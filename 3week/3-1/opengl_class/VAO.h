#pragma once
#include "header.h"

class CVAO
{
private:
	unsigned int m_ID{};
public:
	// 생성 시에 VAO 생성 및 바인딩
	CVAO();
	// 배열 삭제
	~CVAO();
public:
	void Gen();
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

