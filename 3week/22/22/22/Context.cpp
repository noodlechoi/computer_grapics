#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
}

void CContext::Render()
{
    m_program->UseShader();

    auto model = glm::mat4(1.0f);
    m_program->SetUniform("transform", model);

    // ±×¸®±â
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right, red
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right, green
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left, blue
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // top left, yellow

    };

    unsigned int indices[] = {
         0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    m_vao = new CVAO();
    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 6 * 4);

    m_vao->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    m_vao->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (sizeof(float) * 3));

    m_indexbuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(unsigned int) * 6);
}

void CContext::Update()
{
}
