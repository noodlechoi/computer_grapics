#include "Figure.h"

CFigure::CFigure()
{

}

CFigure::CFigure(const GLfloat** const (pos), const GLfloat** const (color))
{
	glGenBuffers(1, &this->m_pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glGenBuffers(1, &this->m_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
}

CFigure::~CFigure()
{
}

void CFigure::initVAO(GLuint& vao)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void CFigure::initVBO(const void* (pos), const void* (color))
{
	glGenBuffers(1, &this->m_pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glGenBuffers(1, &this->m_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
}

void CFigure::draw(GLuint pos_location, GLuint color_location)
{
	// pos vbo 바인딩
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo); // VBO Bind
	glVertexAttribPointer(pos_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	// color vbo 바인딩
	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo); // VBO Bind
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	// 우선 라인을 그린다.
	glDrawArrays(GL_LINES, 0, 2);
}
