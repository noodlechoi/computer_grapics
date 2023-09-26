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

typedef struct Dir
{
	int x, y;
}Dir;

typedef struct Rect
{
	Point p;
	float color[3];
	float size_x;
	float size_y;
	bool is_exist;
	Dir dir;
}Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Motion(int x, int y);

const int rect_cnt = 30;

int winID;
Rect r[rect_cnt];
Rect m_r;
int now_idx;
bool left_button;

void SetColor(Rect& r)
{
	for (int i = 0; i < 3; ++i) {
		r.color[i] = fmod(rand(), 0.9f);
	}
}

void DrawRect(const Rect& r)
{
	glColor3f(r.color[0], r.color[1], r.color[2]);
	glRectf(r.p.x - r.size_x, r.p.y - r.size_y, r.p.x + r.size_x, r.p.y + r.size_y);
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
	if (ConvertPoint(x, y).x <= r.p.x + r.size_x && ConvertPoint(x, y).x >= r.p.x - r.size_x && ConvertPoint(x, y).y <= r.p.y + r.size_y && ConvertPoint(x, y).y >= r.p.y - r.size_y)
		return true;
	else
		return false;
}

// 사각형끼리 충돌 체크
bool RectConflict(const Rect& r1, const Rect& r2)
{
	// 두 좌표 사이의 거리가 두 변 합의 길이보다 작으면 true
	float x = (r1.p.x) - (r2.p.x);
	float y = (r1.p.y) - (r2.p.y);
	x = x < 0 ? x * -1 : x;
	y = y < 0 ? y * -1 : y;

	if (x <= (r1.size_x + r2.size_x) && y <= (r1.size_y + r2.size_y)) {
		return true;
	}
	else
		return false;
}

void MoveRect(Rect& r, const int& x, const int& y)
{
	Point p = ConvertPoint(x, y);

	r.p = p;
}

// 사각형 생성
void ProduceRect(const int& x, const int& y)
{
	// 좌표계 변환
	Point p = ConvertPoint(x, y);

	// 사각형 초기화
	r[now_idx % rect_cnt].p = p;
	r[now_idx % rect_cnt].size_x = 0.05;
	r[now_idx % rect_cnt].size_y = 0.05;
	SetColor(r[now_idx % rect_cnt]);
	r[now_idx % rect_cnt].is_exist = true;

	now_idx++;
}

// 사각형 초기화
void ResetRect()
{
	for (int i = 0; i < rect_cnt; ++i)
		r[i].is_exist = true;
	now_idx = 0;
}

// 지우개 사각형 초기화
void InitRect(Rect& r)
{
	r.size_x = 0.1f;
	r.size_y = 0.1f;
	SetColor(r);
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 5"); // 윈도우 생성(윈도우 이름)

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

	// 사각형 생성
	for (int i = 0; i < rect_cnt; ++i) {
		int x = rand() % WIDTH, y = rand() % HEIGHT;
		ProduceRect(x, y);
	}
	// 지우개 사각형 초기화
	InitRect(m_r);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
화면 지우기
 윈도우를 띄우고 화면에 같은 크기의 작은 사각형을 다양한 색으로 임의의 위치에 20~40개 그린다.
 왼쪽 마우 스 버튼을 누르면 화면의 사각형의 2배의 크기의 사각형(지우개 사각형)이 그려지고, 마우스를 누른
채로 이동시키면 지우개 사각형이 위치를 이동한다.
 지우개 사각형과 부딪친 배경 사각형은 사라진다. 배경 사각형이 사라지면 지우개 사각형의 크기가 커지고 (기
존의 지우개 색상 + 부딪친 사각형 색상)으로 색상을 변경한다..
 왼쪽 마우스 버튼을 떼면 지우개 사각형은 사라진다.
 다시 마우스를 누르면 검정색의 기존의 지우개 사각형 크기로 지우개 사각형이 생긴다.
 키보드 명령어 r: 기존 사각형 삭제되고 새로 그리기
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.1f, 0.1f, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (int i = 0; i < rect_cnt; ++i) {
		if (r[i].is_exist)
			DrawRect(r[i]);
	}
	// 지우개 사각형 그리기
	if(m_r.is_exist)
		DrawRect(m_r);

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left_button = true;
		// 지우개 사각형
		m_r.is_exist = true;
		m_r.p = ConvertPoint(x, y);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		left_button = false;
		m_r.is_exist = false;
	}

}

GLvoid Motion(int x, int y)
{
	if (left_button) {
		// 지우개 사각형 위치 변경
		m_r.p = ConvertPoint(x, y);
		// 닿으면 사각형 제거 후 색깔 더하기
		for (int i = 0; i < rect_cnt; ++i) {
			if (r[i].is_exist) {
				// 충돌 체크
				if (RectConflict(m_r, r[i])) {
					// 지우기
					r[i].is_exist = false;
					// 색깔 더하기, 계속 더하면 검정색이 되므로 나머지 연산 사용
					for (int j = 0; j < 3; ++j) {
						m_r.color[j] = fmod((m_r.color[j] + r[i].color[j]), 0.9f);
					}
					// 사이즈 증가
					m_r.size_x += 0.01f;
					m_r.size_y += 0.01f;
				}
			}
		}

		glutPostRedisplay();
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		now_idx = 0;
		// 사각형 생성
		for (int i = 0; i < rect_cnt; ++i) {
			int x = rand() % WIDTH, y = rand() % HEIGHT;
			ProduceRect(x, y);
		}
		break;
	case 'q':
		glutDestroyWindow(winID);
		std::cout << "프로그램 종료" << std::endl;
		break;
	}

	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다, 호출 시 drawScene로 이동한다!
}