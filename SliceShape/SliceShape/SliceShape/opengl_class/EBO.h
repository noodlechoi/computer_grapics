#pragma once
#include "header.h"

class CEBO
{
private:
	unsigned int m_ID{};
	unsigned int m_index_cnt;
public:
	CEBO();
	CEBO(const void* data, unsigned int index_count);
	~CEBO();
public:
	void Gen(const void* data, unsigned int index_count);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

