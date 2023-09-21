#include <iostream>
#include <ctime>
#include <cmath>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct Point
{
	float x, y;
}Point;

typedef struct Rect
{
	Point p;
	float color[3];
	float size;
}Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

int winID;
Rect r[8];

void SetColor(Rect& r)
{
	for (int i = 0; i < 3; ++i) {
		r.color[i] = fmod(rand(), 0.9f);
	}
}

void DrawRect(const Rect& r)
{
	glColor3f(r.color[0], r.color[1], r.color[2]);
	glRectf(r.p.x - r.size, r.p.y - r.size, r.p.x + r.size, r.p.y + r.size);
}

void SetPoint()
{
	r[0].p = { -0.5f, 0.5f };
	r[1].p = { 0.5f, 0.5f };
	r[2].p = { -0.5f, -0.5f };
	r[3].p = { 0.5f, -0.5f };
	r[4].p = { -0.5f, 0.5f };
	r[5].p = { 0.5f, 0.5f };
	r[6].p = { -0.5f, -0.5f };
	r[7].p = { 0.5f, -0.5f };
	for (int i = 0; i < 8; ++i) {
		r[i].size = 0.5f;
	}
}

Point ConvertPoint(const int& x, const int& y)
{
	Point tmp;
	tmp.x = (double)((x - (double)WIDTH / 2.0) * (double)(1.0 / (double)(WIDTH / 2.0)));
	tmp.y = -(double)((y - (double)HEIGHT / 2.0) * (double)(1.0 / (double)(HEIGHT / 2.0)));

	return tmp;
}

bool Conflict(const Rect& r, const int& x, const int& y)
{
	if (ConvertPoint(x, y).x <= r.p.x + r.size && ConvertPoint(x, y).x >= r.p.x - r.size && ConvertPoint(x, y).y <= r.p.y + r.size && ConvertPoint(x, y).y >= r.p.y - r.size)
		return true;
	else
		return false;
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 2"); // 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	// 랜덤 시드 설정
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 8; ++i) {
		SetColor(r[i]);
	}
	SetPoint();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
윈도우를 띄우고 마우스 명령을 실행 해 본다.
 화면의 가로 세로를 각각 2등분하여 사각형 4개를 그린다.
 네 개의 사각형에 마우스를 클릭하여 색상과 크기를 바꾼다.
 왼쪽 마우스 클릭
 사각형 내부 클릭: 사각형 색상을 랜덤하게 바꾸기
 사각형 외부 클릭: 배경색을 랜덤하게 바꾸기
 오른쪽 마우스 클릭
 사각형 내부 클릭: 사각형 크기 축소
 사각형 외부 클릭: 사각형 크기 확대
=> 사각형 하나 더 위에 만들기
 사각형 그리기 함수
 void glRectf (Glfloat x1, Glfloat y1, Glfloat x2, Glfloat y2);
 (x1, y1): 좌측 하단 좌표값
 (x2, y2): 우측 상단 좌표값
 사각형 색상 바꾸기
 void glColor3f (Glfloat r, Glfloat g, Glfloat b);
 현재 색상 설정하기
 (r, g, b): red, green, blue 색상, 0.0 ~ 1.0 사이의 값으로 glRectf 를 호출하기 직전 설정한다.
** Modern openGL 에서는 사용할 수 없는 deprecated 함수
** 셰이더를 사용하게 되면 이 함수는 사용할 수 없음
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	for (int i = 0; i < 8; ++i) {
		DrawRect(r[i]);
	}

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 4; i < 8; ++i) {
			if (Conflict(r[i], x, y)) {
				SetColor(r[i]);
				glutPostRedisplay();
				return;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (Conflict(r[i], x, y)) {
				SetColor(r[i]);
				glutPostRedisplay();
				return;
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		for (int i = 4; i < 8; ++i) {
			if (Conflict(r[i], x, y)) {
				if(r[i].size > 0.2f)
					r[i].size -= 0.1f;
				glutPostRedisplay();
				return;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (Conflict(r[i], x, y)) {
				if (r[i + 4].size < 0.5f)
					r[i + 4].size += 0.1f;
				glutPostRedisplay();
				return;
			}
		}
	}
}