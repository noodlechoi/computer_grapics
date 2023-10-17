#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct Point
{
	float x, y;
}Point;

GLuint vao, vbo[2];
const GLfloat size = 0.5;

GLfloat rec[4][3] = {
	// 좌 하단
	{-size, -size, 0.0},
	// 우 하단
	{size, -size, 0.0},
	// 좌 상단
	{-size, size, 0.0},
	// 우 상단
	{size, size, 0.0}

};

bool is_click;
bool is_body;
// 이전 인덱스
int idx;
// 이전 좌표
Point before_p;

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("실습 13");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();

	InitBuffer();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

GLvoid drawScene()
{
	// 배경 출력
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	glBindVertexArray(vao);

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);

	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	}
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력

	{

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
	}
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);

	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

/*
마우스를 이용하여 사각형 편집하기
 800x600 크기의 윈도우를 띄운다
 화면 중앙에 사각형을 그린다.
 마우스로 사각형의 꼭짓점을 누르고 드래그하면 꼭짓점이 이동된다.
 사각형의 내부이고 꼭지점과 떨어진 부근을 누르고 드래그하면 사각형이 이동된다.
*/

GLvoid Motion(int x, int y)
{
	if (is_click) {
		Point p = ConvertPoint(x, y);
		rec[idx][0] = p.x;
		rec[idx][1] = p.y;
		glGenBuffers(1, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rec), rec, GL_STATIC_DRAW);

		glutPostRedisplay();
	}
	else if (is_body) {
		Point p = ConvertPoint(x, y);
		for (int i = 0; i < 4; ++i) {
			rec[i][0] += p.x - before_p.x;
			rec[i][1] += p.y - before_p.y;
		}

		glGenBuffers(1, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rec), rec, GL_STATIC_DRAW);
		before_p = p;

		glutPostRedisplay();
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Point p = ConvertPoint(x, y);
		// 꼭짓점
		for (int i = 0; i < 4; ++i) {
			if ((p.x >= rec[i][0] - 0.1 && p.x <= rec[i][0] + 0.1) && (p.y >= rec[i][1] - 0.1 && p.y <= rec[i][1] + 0.1)) {
				is_click = true;
				idx = i;
				return;
			}
		}
		// 전체
		// 좌하단 , 좌상단 , 우하단 , 우상단
		Point max = {}, min = {};
		for (int i = 0; i < 4; ++i) {
			if (rec[i][0] > max.x)
				max.x = rec[i][0];
			if(rec[i][1] > max.y)
				max.y = rec[i][1];
			if (rec[i][0] < min.x)
				min.x = rec[i][0];
			if (rec[i][1] < min.y)
				min.y = rec[i][1];
		}

		if ((p.x > min.x && p.x < max.x) && (p.y > min.y && p.y < max.y)) {
			is_body = true;
			before_p = p;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		is_click = false;
		is_body = false;
	}
}


void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기

	{
		const GLfloat color[3][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rec), rec, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
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