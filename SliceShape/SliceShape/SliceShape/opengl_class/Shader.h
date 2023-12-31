#pragma once
#include "header.h"

class CShader
{
private:
	// 파일 이름
	std::string vertex_file;
	std::string frag_file;

	GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
	GLuint vertexShader, fragmentShader; //--- 세이더 객체
	GLuint shaderID; //--- 셰이더 프로그램
public:
	CShader();
	CShader(std::string vertex, std::string frag);
	~CShader();
public:
	unsigned int GetID();
	// vec 이름 넣기
	int GetLocation(std::string_view name);
	unsigned int GetUniform(std::string_view name);
	void UseShader();
	void MakeShaderProgram();
	void MakeVertexShaders();
	void MakeFragmentShaders();
	char* Filetobuf(const char* file);
};

