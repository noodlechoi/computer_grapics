#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
    if (m_program) {
        delete m_program;
    }
}

void CContext::KeyBoard(const unsigned char& key, const int& x, const int& y)
{
    const float camera_speed = 0.05f;

    // 카메라 x축은 카메라 UP벡터와 z축 벡터의 직교를 단위 벡터로 만든 것이다.
    auto camera_right = glm::normalize(glm::cross(m_camera_up, -m_camera_front));
    auto camera_up = glm::normalize(glm::cross(-m_camera_front, camera_right));
    switch (key) {
    case 'o':
        break;
    case 'x':
        m_camera_pos -= camera_speed * camera_right;
        break;
    case 'X':
        m_camera_pos += camera_speed * camera_right;
        break;
    case 'Z':
        m_camera_pos += camera_speed * m_camera_front;
        break;
    case 'z':
        m_camera_pos -= camera_speed * m_camera_front;
        break;
    case 'w':
        break;
    case 's':
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


    
    m_program->UseShader();

    // 조명
    auto lightModelTransform = glm::translate(glm::mat4(1.0), m_light.position) *
                                glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
    m_program->SetUniform("lightPos", m_light.position);
    m_program->SetUniform("light.ambient", glm::vec3(1.0f));
    m_program->SetUniform("material.ambient", glm::vec3(1.0f));
    m_program->SetUniform("transform", projection * view * lightModelTransform);
    m_program->SetUniform("modelTransform", lightModelTransform);
    m_program->SetUniform("invModelTransform", transpose(inverse(lightModelTransform)));

    m_box->Draw(m_program);

    // 모델 조명
    m_program->SetUniform("viewPos", m_camera_pos);
    m_program->SetUniform("light.position", m_light.position);
    m_program->SetUniform("light.ambient", m_light.ambient);
    m_program->SetUniform("light.diffuse", m_light.diffuse);
    m_program->SetUniform("light.specular", m_light.specular);
    m_program->SetUniform("material.ambient", m_material.ambient);
    m_program->SetUniform("material.diffuse", m_material.diffuse);
    m_program->SetUniform("material.specular", m_material.specular);
    m_program->SetUniform("material.shininess", m_material.shininess);


    // 모델 변환
    auto model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(1.0f, 0.0f, 0.0f));
 
    auto transform = projection * view * model;
    // transform, model 변환 행렬 전달
    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    
    //m_model.Draw(m_program);

    for (auto mesh : m_meshes) {
        mesh->Draw(m_program);
    }
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    //m_model.Create("res/sphere.obj");
    //m_model.Create("res/box.txt");

    m_box = new CMesh;
    m_box->CreateBox();

    m_meshes.push_back(new CMesh);
    m_meshes[0]->CreateSquarePy();
}

void CContext::Update()
{
}