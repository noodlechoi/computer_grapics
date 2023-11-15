#pragma once
#include "header.h"
#include "Type.h"

class CVBO
{
private:
	unsigned int m_ID{};
	unsigned int m_type;
public:
	CVBO();
	CVBO(const void* data, const unsigned int size, const unsigned int type);
	~CVBO();
public:
	unsigned int GetID();
	void Gen(const void* data, const unsigned int size, const unsigned int type);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
	void Draw() const;
	unsigned int GetType();
};

