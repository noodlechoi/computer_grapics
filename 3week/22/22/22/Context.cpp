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


void CContext::KeyBoard(const unsigned char& key, const int& x, const int& y)
{
    switch (key) {
    case 'o':

        break;
    default:
        break;
    }
}

void CContext::Mouse(const int& button, const int& state, const int& x, const int& y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        m_prev_mousePos = CGL::GetInstance()->ConvertPoint(x, y);
        m_camera_control = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        m_camera_control = false;
    }
}

void CContext::Motion(const int& x, const int& y)
{
    if (!m_camera_control) return;

    auto pos = CGL::GetInstance()->ConvertPoint(x, y);
    auto deltaPos = pos - m_prev_mousePos;

    const float cameraRotSpeed = 3.0f;
    m_camera_yaw += deltaPos.x * cameraRotSpeed;
    m_camera_pitch -= deltaPos.y * cameraRotSpeed;

    if (m_camera_yaw < 0.0f)   m_camera_yaw += 360.0f;
    if (m_camera_yaw > 360.0f) m_camera_yaw -= 360.0f;

    if (m_camera_pitch > 89.0f)  m_camera_pitch = 89.0f;
    if (m_camera_pitch < -89.0f) m_camera_pitch = -89.0f;

    m_prev_mousePos = pos;

}

void CContext::Render()
{
    m_program->UseShader();

    m_camera_front = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    auto projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 20.0f);

    auto view = glm::lookAt(
        m_camera_pos,
        m_camera_pos + m_camera_front,
        m_camera_up);

    auto model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    auto transform = projection * view * model;
    m_program->SetUniform("transform", transform);

    // 그리기
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    float vertices[] = {
        // 육면체
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        // color different
        // blue
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 0
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,// 1
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,// 2
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,// 3

        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 4
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 5
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 6
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 7

        // green
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // 0
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,// 1
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// 2
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,// 3

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // 4
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // 5
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 6
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 7

    };

    unsigned int indices[] = {
        // left
         0, 3, 2, 0, 2, 1,
         // up
         0 + 8, 4 + 8, 3 + 8, 3 + 8, 4 + 8, 7 + 8,
         // right
         4 , 5, 6, 4, 6, 7,
         // front
         0 + 16, 5 + 16, 4 + 16, 0 + 16, 1 + 16, 5 + 16,
         // down
         1 + 8, 2 + 8, 5 + 8, 2 + 8, 6 + 8, 5 + 8,
         // back
         3 + 16, 7 + 16, 6 + 16, 3 + 16, 6 + 16, 2 + 16,
    };

    m_vao = new CVAO();
    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 6 * 4 * 6);

    m_vao->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    m_vao->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (sizeof(float) * 3));

    m_indexbuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(unsigned int) * 6 * 6);
}

void CContext::Update()
{
    std::cout << "update" << std::endl;
}