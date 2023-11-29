#include "Orbit.h"

COrbit::COrbit()
{
}


COrbit::~COrbit()
{
}

void COrbit::Init(const std::vector<Vertex>& vertices)
{
    m_vao = new CVAO();

    m_vao->Gen();

    m_vertexbuffer = new CBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), sizeof(Vertex), vertices.size());

    m_vao->SetAttrib(0, 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, position));
    m_vao->SetAttrib(1, 3, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, normal));
}

void COrbit::Draw(const CShader* program) const
{
    m_vao->Bind();
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}


void COrbit::update()
{

}