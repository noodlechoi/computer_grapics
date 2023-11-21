#pragma once
#include "header.h"

// VBO, EBO  ¹öÆÛ ÀúÀå Å¬·¡½º
class CBuffer
{
private:
	unsigned int m_buffer{};
	unsigned int m_bufferType{};
	unsigned int m_usage{};
public:
	CBuffer();
	CBuffer(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int m_size);
	~CBuffer();
public:

	void Gen(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int m_size);
	void Bind() const;
};