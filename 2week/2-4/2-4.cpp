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
	bool is_exist;
}Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

int winID;
Rect r[5];
int now_idx;

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

// 마우스 클릭 시 사각형 생성
void ProduceRect(const int& x, const int& y)
{
	if (now_idx < 5) {
		// 좌표계 변환
		Point p = ConvertPoint(x, y);
		// 사각형 초기화
		r[now_idx].p = p;
		SetColor(r[now_idx]);
		r[now_idx].size = 0.1;
		r[now_idx].is_exist = true;
	}
	// 좌표만 변환
	else {
		// 좌표계 변환
		Point p = ConvertPoint(x, y);
		// 사각형 초기화
		r[now_idx % 5].p = p;
		SetColor(r[now_idx % 5]);
	}
	now_idx++;
}

// 사각형 초기화
void ResetRect()
{
	for (int i = 0; i < 5; ++i)
		r[i].is_exist = false;
	now_idx = 0;
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 4"); // 윈도우 생성(윈도우 이름)

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

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
사각형에 애니메이션 적용하기
 배경색은 짙은 회색으로 정하고, 사각형은 랜덤한 색으로 그린다.
 마우스를 클릭하는 곳이 중심이 되어 사각형을 그린다. 최대 5개의 사각형을 그린다.
 키보드 입력 (명령어는 대문자 또는 소문자 무관함):
 a: 위치 변화1  사각형들은 각각 대각선으로 이동하고 벽에 닿으면 튕겨 다른 방향으로 이동한다/멈춘다.
 i: 위치 변화2  사각형들이 지그재그로 이동한다/멈춘다.
 c: 크기 변화  사각형의 크기가 다양하게 변한다/변하지 않는다.
 o: 색상 변화  사각형의 색상이 랜덤하게 변한다/변하지 않는다.
 s: 모든 애니메이션이 멈춘다.
 m: 원래 그린 위치로 사각형들이 이동한다.
 r: 사각형들을 삭제하고 다시 마우스 입력을 받을 수 있다.
 q: 프로그램을 종료한다

=> 타임함수 키에 따라 함수 다르게 출력
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.1f, 0.1f, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (int i = 0; i < 5; ++i) {
		if(r[i].is_exist)
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
		ProduceRect(x, y);
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		break;
	case 'i':
		break;
	case 'c':
		break;
	case 'o':
		for (int i = 0; i < 5; ++i) {
			if (r[i].is_exist)
				SetColor(r[i]);
		}
		break;
	case 's':
		break;
	case 'm':
		break;
	case 'r':
		ResetRect();
		break;
	case 'q':
		glutDestroyWindow(winID);
		std::cout << "프로그램 종료" << std::endl;
		break;
	}

	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다, 호출 시 drawScene로 이동한다!
}