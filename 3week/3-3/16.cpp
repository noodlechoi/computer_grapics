#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#define WIDTH 800
#define HEIGHT 600

typedef struct Point
{
	float x, y;
}Point;


GLuint vao, center_vbo, center_c_vbo, four_idx, four_list;

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void InitBuffer();
char* filetobuf(const char*);

Point ConvertPoint(const int& x, const int& y)
{
	Point tmp;
	tmp.x = (double)((x - (double)WIDTH / 2.0) * (double)(1.0 / (double)(WIDTH / 2.0)));
	tmp.y = -(double)((y - (double)HEIGHT / 2.0) * (double)(1.0 / (double)(HEIGHT / 2.0)));

	return tmp;
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("실습 14");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();

	InitBuffer();

	// 깊이 검사 설정
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	// 깊이 
	glDisable(GL_DEPTH_TEST);

}

/*
3차원 객체, 육면체 또는 사면체의 면을 명령어에 따라 그리기
 모든 객체들은 X축으로 10도, y축으로 10도 회전해서 그린다. (3차원 도형이라 약간 기울어지게 그린다)
 다음의 키보드 명령어에 따라 도형을 구성하는 각 면을 그린다. 각 면마다 색상을 정해 해당 색상으로 그린다.
 1/2/3/4/5/6: 육면체의 각 면을 그린다.
 7/8/9/0 : 사면체의 각 면을 그린다.
 c: 육면체에서 랜덤한 2개의 면을 그린다.
 t: 사면체에서 랜덤한 2개의 면을 그린다.
*/

GLvoid drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 좌표축 그리기
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	glBindVertexArray(vao);

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);

	// 좌표축 그리기
	for (int i = 0; i < 2; ++i) {
		{
			glBindBuffer(GL_ARRAY_BUFFER, center_vbo); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(i * 6 * sizeof(float)));
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, center_c_vbo); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(i * 6 * sizeof(float)));
		}
		glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
	}

	glBindBuffer(GL_ARRAY_BUFFER, four_list); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);

	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;
	case '9':
		break;
	case '0':
		break;
	case 'c':
		break;
	case 't':
		break;
	default:
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
}


void InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	{
		// 좌표축
		const GLfloat center_line[6][3] = {
			// x축
			{-1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
			// y축
			{0.0, -1.0, 0.0}, {0.0, 1.0, 0.0},
			// z축
			{0.0, 0.0, -1.0}, {0.0, 0.0, 1.0}
		};
		const GLfloat center_color[6][3] = {
			// x축
			{1.0, 0.0, 0.0},{1.0, 0.0, 0.0},
			// y축
			{0.0, 1.0, 0.0},{0.0, 1.0, 0.0},
			// z축
			{0.0, 0.0, 1.0},{0.0, 0.0, 1.0}
		};

		glGenBuffers(1, &center_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, center_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(center_line), center_line, GL_STATIC_DRAW);
		glGenBuffers(1, &center_c_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, center_c_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(center_color), center_color, GL_STATIC_DRAW);
	}

	{
		// four solid
		const GLfloat size = 0.3;
		const GLfloat data[5][3] = {
			// pos
			{0.0, 0.0, 0.0},	// 0
			{size, 0.0, 0.0},	// 1
			{0.0,size, 0.0},	// 2
			{0.0, 0.0, size},	// 3
			// color
			{0.5, 0.5, 0.0}		// 4
		};

		// index buffer
		GLuint four_idx_buff[] = {
			// pos
			0, 2, 1, 0, 3, 2, 0, 1, 3, 2, 3, 1,
			// color
			4, 4, 4
		};

		glGenBuffers(1, &four_list);
		glBindBuffer(GL_ARRAY_BUFFER, four_list);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);


		glGenBuffers(1, &four_idx);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, four_idx);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(four_idx_buff), four_idx_buff, GL_STATIC_DRAW);
	}
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}