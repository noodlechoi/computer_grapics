#pragma once
#include "header.h"

class CVAO
{
private:
	unsigned int m_ID{};
public:
	// ���� �ÿ� VAO ���� �� ���ε�
	CVAO();
	// �迭 ����
	~CVAO();
public:
	void Gen();
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

