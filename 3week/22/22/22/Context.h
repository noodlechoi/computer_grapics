#pragma once
#include "opengl_class/header.h"
#include "opengl_class/header_user.h"

class CContext
{
private:
	CShader* m_program;
	CVAO* m_vao;
	CBuffer* m_vertexbuffer;
	CBuffer* m_indexbuffer;
public:
	CContext();
	~CContext();
public:
	void Init();
	void Render();
	void Update();
};

