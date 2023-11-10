#pragma once
#include "header.h"

// ��� �������� ���� Ŭ����
class CFigure
{
private:
	GLuint m_pos_vbo;
	GLuint m_color_vbo;
public:
	CFigure();
	CFigure(const GLfloat** const (pos), const GLfloat** const (color));
	~CFigure();
public:
	// VAO ���� �� ���ε�, ���� : vao ����
	void initVAO(GLuint& vao);
	// VBO ���ε�
	void initVBO(const void* (pos), const void* (color));
	// line�� �׸�
	virtual void draw(GLuint pos_location, GLuint color_location);
};

