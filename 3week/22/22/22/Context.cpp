#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
    if (m_program) {
        delete m_program;
    }
    if (m_vao) {
        delete m_vao;
    }
    if (m_vertexbuffer) {
        delete m_vertexbuffer;
    }
    if (m_indexbuffer) {
        delete m_indexbuffer;
    }
}

/*
o / O: 앞면이 좌우로 열린다.
w/a/s/d: 로봇이 앞/뒤/좌/우 방향으로 이동 방향을 바꿔서 걷는다. 가장자리에 도달하면 로봇은 뒤로 돌아 다시 걷는다
+/-: 걷는 속도가 빨라지거나/느려진다.
j: 로봇이 제자리에서 점프한다.
i: 모든 변환을 리셋하고 다시 시작
z/Z: 앞뒤로 이동
x/X: 좌우로 이동
y/Y: 카메라가 현재 위치에서 화면 중심 y축을 기준으로 공전
*/

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

    const float object_speed = 3.0f;
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
    m_program->SetUniform("viewPos", m_camera_pos);
    m_program->SetUniform("lightPos", m_light_color);
    m_program->SetUniform("lightColor", m_light_color);
    m_program->SetUniform("objectColor", m_object_color);
    m_program->SetUniform("ambientStrength", m_ambient_strength);
    m_program->SetUniform("specularStrength", m_spec_strength);
    m_program->SetUniform("specularShininess", m_spec_shininess);


    // 모델 변환
    auto model = glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(1.0f, 0.0f, 0.0f));
    auto transform = projection * view * model;
    // transform, model 변환 행렬 전달
    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    m_program->SetUniform("invModelTransform", transpose(inverse(model)));

    // 그리기
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    };

    uint32_t indices[] = {
         0,  2,  1,  2,  0,  3,
         4,  5,  6,  6,  7,  4,
         8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
    };

    m_vao = new CVAO();
    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, (sizeof(float) * 6 * 6 * 4));

    m_vao->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    m_vao->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (sizeof(float) * 3));

    m_indexbuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(unsigned int) * 6 * 6);
}

void CContext::Update()
{
}