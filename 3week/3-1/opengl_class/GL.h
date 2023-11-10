#pragma once
#include "header.h"

class CGL
{
private:
	CGL();
	~CGL();
public:
	// ��ü �ϳ��� ����
	static CGL* GetInstance()
	{
		static CGL m_g;
		return &m_g;
	}
public:
	// name : window name
	void initWindow(int argc, char** argv, const int& x, const int& y, std::string_view name);
	
};