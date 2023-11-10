#include "VBO.h"

CVBO::CVBO()
{
}

CVBO::CVBO(const void* data, const unsigned int size)
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. ���� ����
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. ���ε�("�۾� ����")
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);  //3. �۾� ���� ���ۿ� ������ ����
}

CVBO::~CVBO()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

unsigned int CVBO::GetID()
{
	return m_ID;
}

void CVBO::Gen(const void* data, const unsigned int size)
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. ���� ����
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. ���ε�("�۾� ����")
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);  //3. �۾� ���� ���ۿ� ������ ����
}

void CVBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
}

void CVBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CVBO::Delete() const
{
	glDeleteVertexArrays(1, &this->m_ID);
}
