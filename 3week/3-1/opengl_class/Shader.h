#pragma once
#include "header.h"

class CShader
{
private:
	// ���� �̸�
	std::string vertex_file;
	std::string frag_file;

	GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
	GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
	GLuint shaderID; //--- ���̴� ���α׷�
public:
	CShader();
	CShader(std::string vertex, std::string frag);
	~CShader();
public:
	unsigned int getID();
	// vec �̸� �ֱ�
	int getLocation(std::string_view name);
	void useShader();
	void makeShaderProgram();
	void makeVertexShaders();
	void makeFragmentShaders();
	char* filetobuf(const char* file);
	void set(const std::string_view name, bool value) const;
	void set(const std::string_view name, int value) const;
	void set(const std::string_view name, float value) const;

};

