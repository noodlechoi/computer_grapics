#pragma once
#include "header.h"

class CVBO
{
private:
	unsigned int m_ID{};
public:
	CVBO();
	CVBO(const void* data, const unsigned int size);
	~CVBO();
public:
	unsigned int GetID();
	void Gen(const void* data, const unsigned int size);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

