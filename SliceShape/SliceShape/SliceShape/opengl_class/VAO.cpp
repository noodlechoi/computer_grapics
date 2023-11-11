#include "VAO.h"

CVAO::CVAO()
{
	//if (!m_ID)
	//{
	//	glGenVertexArrays(1, &this->m_ID); //vao 持失
	//}
	//// bind
	//glBindVertexArray(this->m_ID);
}

CVAO::~CVAO()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

void CVAO::Gen()
{
	if (!m_ID)
	{
		glGenVertexArrays(1, &this->m_ID); //vao 持失
	}
	// bind
	glBindVertexArray(this->m_ID);
}

void CVAO::Bind() const
{
	glBindVertexArray(this->m_ID);
}

void CVAO::Unbind() const
{
	glBindVertexArray(0);
}

void CVAO::Delete() const
{
	glDeleteVertexArrays(1, &this->m_ID);
}
