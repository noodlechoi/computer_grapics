#pragma once
#include "header.h"
#include "Type.h"

class CGL
{
private:
	CGL();
	~CGL();
public:
	// 객체 하나만 생성
	static CGL* GetInstance()
	{
		static CGL m_g;
		return &m_g;
	}
public:
	// name : window name
	void InitWindow(int argc, char** argv, const int& x, const int& y, std::string_view name);
	void Render(void (*funcptr)(void));
	Point ConvertPoint(const int& x, const int& y);
};