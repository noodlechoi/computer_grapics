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
    case 'c':
        color_cnt = (color_cnt + 1) % 4;
        if (color_cnt == 0) {
            m_light_color = glm::vec3(1.0f, 1.0f, 1.0f);
        }
        else if (color_cnt == 1) {
            m_light_color = glm::vec3(0.2f, 0.4f, 0.7f);
        }
        else if (color_cnt == 2) {
            m_light_color = glm::vec3(0.6f, 1.0f, 0.1f);
        }
        else if (color_cnt == 3) {
            m_light_color = glm::vec3(0.8f, 0.3f, 0.3f);
        }
        break;
    case 'R':
        R_flag = !R_flag;
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

    auto projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 40.0f);

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
    m_program->SetUniform("lightColor", m_light_color);
    m_program->SetUniform("objectColor", glm::vec3(1.0f));
    m_program->SetUniform("ambientStrength", 1.0f);
    m_program->SetUniform("transform", projection * view * lightModelTransform);
    m_program->SetUniform("modelTransform", lightModelTransform);
    m_program->SetUniform("invModelTransform", transpose(inverse(lightModelTransform)));

    box->Draw(m_program);
    
    

    std::vector<glm::vec3> circle_pos = {
        glm::vec3(4.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        glm::vec3(-4.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };
    float size[] = {0.2, 0.1, 0.05 };

    // 모델 변환
    for (int i = 0; i < 3; ++i) {
        // 모델 조명
        m_program->SetUniform("viewPos", m_camera_pos);
        m_program->SetUniform("lightPos", light_pos);
        m_program->SetUniform("lightColor", m_light_color);
        m_program->SetUniform("ambientStrength", m_ambient_strength);
        m_program->SetUniform("specularStrength", m_spec_strength);
        m_program->SetUniform("specularShininess", m_spec_shininess);

        m_program->SetUniform("objectColor", circle_pos[i * 2 + 1]);

        auto model = glm::translate(glm::mat4(1.0), circle_pos[i*2])
            * glm::scale(glm::mat4(1.0f), glm::vec3(size[i], size[i], size[i]))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
 
        auto transform = projection * view * model;
        // transform, model 변환 행렬 전달
        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    
        m_model.Draw(m_program);
    }

    //for (auto mesh : m_meshes) {
    //    mesh->Draw(m_program);
    //}
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();


    box = new CMesh;
    box->CreateBox();

    m_model.Create("res/sphere.obj");
}

void CContext::Update()
{
}

void CContext::Time(int value)
{
    if (value == 1) {
        if (r_flag) {
            m_light_obj_y += 10;
        }
        else if (R_flag) {
            m_light_obj_y -= 10;
        }
        glutPostRedisplay();
    }
}
