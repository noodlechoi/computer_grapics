#include "EBO.h"

CEBO::CEBO()
{
}

CEBO::CEBO(const void* data, unsigned int index_count)
{
	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. 버퍼 생성
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. 바인딩("작업 상태")
	glBufferData(GL_ARRAY_BUFFER, index_count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);  //3. 작업 상태 버퍼에 데이터 전달
}

CEBO::~CEBO()
{
	glDeleteVertexArrays(1, &this->m_ID);
}

void CEBO::Gen(const void* data, unsigned int index_count)
{

	if (!this->m_ID)
	{
		glGenBuffers(1, &this->m_ID); //1. 버퍼 생성
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); //2. 바인딩("작업 상태")
	glBufferData(GL_ARRAY_BUFFER, index_count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);  //3. 작업 상태 버퍼에 데이터 전달
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
