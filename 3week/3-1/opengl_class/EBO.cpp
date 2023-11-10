#include "EBO.h"

CEBO::CEBO()
{
}

CEBO::CEBO(const void* data, unsigned int index_count)
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. ���� ����
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. ���ε�("�۾� ����")
	glBufferData(GL_ARRAY_BUFFER, index_count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);  //3. �۾� ���� ���ۿ� ������ ����
}

CEBO::~CEBO()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

void CEBO::Gen(const void* data, unsigned int index_count)
{

	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. ���� ����
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. ���ε�("�۾� ����")
	glBufferData(GL_ARRAY_BUFFER, index_count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);  //3. �۾� ���� ���ۿ� ������ ����
}

void CEBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
}

void CEBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CEBO::Delete() const
{
	glDeleteVertexArrays(1, &this->m_ID);
}
