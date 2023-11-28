#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
    if (m_program) {
        delete m_program;
    }
    for (auto& mesh : m_meshes) {
        delete mesh;
    }
}

void CContext::KeyBoard(const unsigned char& key, const int& x, const int& y)
{
    const float camera_speed = 0.05f;

    // 카메라 x축은 카메라 UP벡터와 z축 벡터의 직교를 단위 벡터로 만든 것이다.
    auto camera_right = glm::normalize(glm::cross(m_camera_up, -m_camera_front));
    auto camera_up = glm::normalize(glm::cross(-m_camera_front, camera_right));
    switch (key) {
    case 'n':
        n_flag = !n_flag;
        break;
    case 'm':
        m_flag = !m_flag;
        break;
    case 'y':
        y_flag = !y_flag;
        break;
    case 'Z':
        radius.x += 0.1f;
        break;
    case 'z':
        radius.x -= 0.1f;
        break;
    case 'r':
        r_flag = !r_flag;
        break;
    case 'q':
        exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}

void CContext::Mouse(const int& button, const int& state, const int& x, const int& y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        m_prev_pos = CGL::GetInstance()->ConvertPoint(x, y);
        m_camera_control = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        m_camera_control = false;
    }
    glutPostRedisplay();
}

void CContext::Motion(const int& x, const int& y)
{
    if (!m_camera_control) return;

    auto pos = CGL::GetInstance()->ConvertPoint(x, y);
    auto deltaPos = pos - m_prev_pos;

    const float object_speed = 10.0f;
    m_obj_radian_x += deltaPos.x * object_speed;
    m_obj_radian_y -= deltaPos.y * object_speed;

    m_prev_pos = pos;

    glutPostRedisplay();
}

void CContext::Render()
{

    m_camera_front = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    auto projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 20.0f);

    auto view = glm::lookAt(
        m_camera_pos,
        m_camera_pos + m_camera_front,
        m_camera_up);

    // 조명 위치 계산
    glm::vec3 light_pos(0.0f, 0.0f, 0.0f);
    auto light_trans = glm::rotate(glm::mat4(1.0f), glm::radians(m_light_obj_y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0), radius);
    light_pos = light_trans * glm::vec4(light_pos, 1.0f);

    // 조명 객체
    auto lightModelTransform = glm::translate(glm::mat4(1.0), light_pos) *
                               glm::scale(glm::mat4(1.0), glm::vec3(0.5f));
    m_program->UseShader();
    
    m_program->SetUniform("lightPos", light_pos);
    m_program->SetUniform("lightColor", glm::vec3(1.0f));
    m_program->SetUniform("objectColor", glm::vec3(1.0f));
    m_program->SetUniform("ambientStrength", 1.0f);
    m_program->SetUniform("transform", projection * view * lightModelTransform);
    m_program->SetUniform("modelTransform", lightModelTransform);
    m_program->SetUniform("invModelTransform", transpose(inverse(lightModelTransform)));

    if (m_flag) {
        m_program->SetUniform("lightColor", glm::vec3(0.1f));
    }

    m_meshes[0]->Draw(m_program);
    
    // 모델 조명
    m_program->SetUniform("viewPos", m_camera_pos);
    m_program->SetUniform("lightPos", light_pos);
    m_program->SetUniform("lightColor", m_light_color);
    m_program->SetUniform("objectColor", m_object_color);
    m_program->SetUniform("ambientStrength", m_ambient_strength);
    m_program->SetUniform("specularStrength", m_spec_strength);
    m_program->SetUniform("specularShininess", m_spec_shininess);

    if (m_flag) {
        m_program->SetUniform("lightColor", glm::vec3(0.1f));
    }

    // 모델 변환
    auto model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
 
    auto transform = projection * view * model;
    // transform, model 변환 행렬 전달
    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    
    if (!n_flag) {
        m_meshes[0]->Draw(m_program);
    }
    else {
        m_meshes[1]->Draw(m_program);
    }

    //m_model.Draw(m_program);

    //for (auto mesh : m_meshes) {
    //    mesh->Draw(m_program);
    //}
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    //m_model.Create("res/sphere.obj");
    //m_model.Create("res/box.txt");

    m_meshes.push_back(new CMesh);
    m_meshes[0]->CreateBox();

    m_meshes.push_back(new CMesh);
    m_meshes[1]->CreateSquarePy();
}

void CContext::Update()
{
}

void CContext::Time(int value)
{
    if (value == 1) {
        if (y_flag) {
            m_obj_radian_y += 10;
        }
        if (r_flag) {
            m_light_obj_y += 10;
        }
        glutPostRedisplay();
    }
}
