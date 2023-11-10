#pragma once
#include "header.h"

// 모든 도형들의 기초 클래스
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
	// VAO 생성 및 바인딩, 인자 : vao 변수
	void initVAO(GLuint& vao);
	// VBO 바인딩
	void initVBO(const void* (pos), const void* (color));
	// line을 그림
	virtual void draw(GLuint pos_location, GLuint color_location);
};

