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

const GLfloat size = 10.0;
GLfloat vertexPos[3][3];
GLfloat vertexCol[3][3];
GLuint vao; //, vbo[2];

GLuint TriPosVbo[10], TriColorVbo[10];
int idx;


GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void InitVAO();
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
	glutCreateWindow("Example1");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();

	// vbo
	InitBuffer();

	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 쉐이터 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	glBindVertexArray(vao);

	for (int i = 0; i < 10; ++i) {

		// Location 번호 저장
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

		glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
		glEnableVertexAttribArray(ColorLocation);

		{
			glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력

		glDisableVertexAttribArray(PosLocation); // Disable 필수!
		glDisableVertexAttribArray(ColorLocation);
	}
	


	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

/*
화면에 기본 도형 그리기
 키보드 명령에 따라, 마우스를 누르는 위치에 점, 선, 삼각형 또는 사각형 (삼각형 2개 붙이기) 그린다.
 색상과 크기는 자율적으로 정하고, 최대 10개의 도형을 그린다.
 키보드 명령
 p: 점 그리기
 l: 선 그리기
 t: 삼각형 그리기
 r: 사각형 그리기
 w/a/s/d: 그린 모든 도형이 화면에서 위/좌/아래/우측으로 이동한다.
 c: 모든 도형을 삭제한다

클릭 시 점 그리는 거
*/
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// 클릭한 부분으로 초기화
		const GLfloat size = 0.3f;
		Point p = ConvertPoint(x, y);
		
		vertexPos[0][0] = p.x;
		vertexPos[0][1] = p.y + size;
		vertexPos[0][2] = 0.0;

		vertexPos[1][0] = p.x - size;
		vertexPos[1][1] = p.y - size;
		vertexPos[1][2] = 0.0;

		vertexPos[2][0] = p.x + size;
		vertexPos[2][1] = p.y - size;
		vertexPos[2][2] = 0.0;

		for (int i = 0; i < 3; ++i) {
			vertexCol[i][0] = p.x;
			vertexCol[i][1] = p.y;
			vertexCol[i][2] = 0;
		}

		// vbo
		InitBuffer();
	}
}

void InitVAO()
{
	
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기

	glGenBuffers(1, &TriPosVbo[idx % 10]);
	glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo[idx % 10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	glGenBuffers(1, &TriColorVbo[idx % 10]);
	glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo[idx % 10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCol), vertexCol, GL_STATIC_DRAW);
	idx++;
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