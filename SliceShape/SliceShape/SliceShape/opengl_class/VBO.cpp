#include "VBO.h"

CVBO::CVBO() : m_type{ static_cast<unsigned int>(EShape::line) }
{
}

CVBO::CVBO(const void* data, const unsigned int size, const unsigned int type) : m_type{ type }
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. 버퍼 생성
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. 바인딩("작업 상태")
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);  //3. 작업 상태 버퍼에 데이터 전달
}

CVBO::~CVBO()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

unsigned int CVBO::GetID()
{
	return m_ID;
}

void CVBO::Gen(const void* data, const unsigned int size, const unsigned int type)
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. 버퍼 생성
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. 바인딩("작업 상태")
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);  //3. 작업 상태 버퍼에 데이터 전달
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

void CVBO::Draw() const
{
	switch (m_type)	{
	case static_cast<unsigned int>(EShape::dot):
		glPointSize(5);
		glDrawArrays(GL_POINTS, 0, 1);
		break;
	case static_cast<unsigned int>(EShape::line):
		glLineWidth(5);
		glDrawArrays(GL_LINES, 0, 2);
		break;
	case static_cast<unsigned int>(EShape::tri):
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	case static_cast<unsigned int>(EShape::rec):
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	default:
		break;
	}
}

unsigned int CVBO::GetType()
{
	return this->m_type;
}
