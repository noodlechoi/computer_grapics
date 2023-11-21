#include "Buffer.h"

CBuffer::CBuffer()
{
}

CBuffer::CBuffer(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int m_size) : m_bufferType{ bufferType }, m_usage{ usage }
{
	if (!m_buffer)
	{
		glGenBuffers(1, &m_buffer); //1. ���� ����
	}
	CBuffer::Bind();
	glBufferData(bufferType, m_size, data, usage);  //3. �۾� ���� ���ۿ� ������ ����
}

CBuffer::~CBuffer()
{
	if (m_buffer) {
		glDeleteVertexArrays(1, &this->m_buffer);
	}
}


void CBuffer::Gen(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int m_size)
{
	if (!m_bufferType || !m_usage) {
		m_bufferType = bufferType;
		m_usage = usage;
	}

	if (!m_buffer)
	{
		glGenBuffers(1, &m_buffer); //1. ���� ����
	}
	CBuffer::Bind();
	glBufferData(bufferType, m_size, data, usage);  //3. �۾� ���� ���ۿ� ������ ����
}


void CBuffer::Bind() const
{
	glBindBuffer(m_bufferType, m_buffer);
}