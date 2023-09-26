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
GLvoid TimerFunction(int value);

const int rect_cnt = 5;
const int disappear = rect_cnt * 8;

int winID;
Rect r[rect_cnt];
Rect r_d[disappear];
int now_idx;
int dis_idx;
bool start_cross, start_updown;

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
	r[now_idx % rect_cnt].size_x = 0.1;
	r[now_idx % rect_cnt].size_y = 0.1;
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

// 사라지는 사각형 초기화
void ResetDisRect(const Rect& r, int cnt)
{
	r_d[dis_idx % disappear].p = r.p;
	r_d[dis_idx % disappear].is_exist = true;
	r_d[dis_idx % disappear].size_x = r.size_x * (cnt * 0.1);
	r_d[dis_idx % disappear].size_y = r.size_y * (cnt * 0.1);

	for (int j = 0; j < 3; ++j)
		r_d[dis_idx % disappear].color[j] = r.color[j];

	dis_idx++;
}

// 분해
void CrossReplaceDisRect(int i, int j)
{
	int idx = dis_idx % disappear - 1;
	if (j == 0) {
		r_d[idx].p = { r[i].p.x - r[i].size_x / 2,  r[i].p.y - r[i].size_y / 2 };
		r_d[idx].dir = { -1, -1 };
	}
	else if (j == 1) {
		r_d[idx].p = { r[i].p.x + r[i].size_x / 2,  r[i].p.y + r[i].size_y / 2 };
		r_d[idx].dir = { 1, 1 };
	}
	else if (j == 2) {
		r_d[idx].p = { r[i].p.x - r[i].size_x / 2,  r[i].p.y + r[i].size_y / 2 };
		r_d[idx].dir = { -1, 1 };
	}
	else if (j == 3) {
		r_d[idx].p = { r[i].p.x + r[i].size_x / 2,  r[i].p.y - r[i].size_y / 2 };
		r_d[idx].dir = { 1, -1 };
	}
}

void UpDownReplaceDisRect(int i, int j)
{
	int idx = dis_idx % disappear - 1;
	if (j == 0) {
		r_d[idx].p = { r[i].p.x - r[i].size_x / 2,  r[i].p.y - r[i].size_y / 2 };
		r_d[idx].dir = { 0, -1 };
	}
	else if (j == 1) {
		r_d[idx].p = { r[i].p.x + r[i].size_x / 2,  r[i].p.y + r[i].size_y / 2 };
		r_d[idx].dir = { 0, 1 };
	}
	else if (j == 2) {
		r_d[idx].p = { r[i].p.x - r[i].size_x / 2,  r[i].p.y + r[i].size_y / 2 };
		r_d[idx].dir = { -1, 0 };
	}
	else if (j == 3) {
		r_d[idx].p = { r[i].p.x + r[i].size_x / 2,  r[i].p.y - r[i].size_y / 2 };
		r_d[idx].dir = { 1, 0 };
	}
}

void AllReplaceDisRect(int i, int j)
{

}

void MoveRect(Rect& r)
{
	r.p.x += 0.02f * r.dir.x;
	r.p.y += 0.02f * r.dir.y;
	r.size_x -= 0.005f;
	r.size_y -= 0.005f;

	if (r.size_x <= 0.0f || r.size_y <= 0.0f) {
		r.is_exist = false;
	}
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

	for (int i = 0; i < 5; ++i) {
		int x = rand() % WIDTH, y = rand() % HEIGHT;
		ProduceRect(x, y);
	}

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
퍼져 나가는 사각형 애니메이션
 화면의 랜덤한 위치에 5개의 사각형을 랜덤한 색상으로 그린다.
 마우스로 사각형 내부를 클릭하면, 사각형은 사등분되어
 위치를 이동한다.
 이 때, 사각형은 크기가 점점 작아지며 특정 크기가 되면 사라진다.
 위치 이동 애니메이션
① 좌우상하 이동
② 대각선 이동
③ 좌우상하대각선 이동 (이때는 축소된 사각형이 8개 나타난다).
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.1f, 0.1f, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (int i = 0; i < rect_cnt; ++i) {
		if (r[i].is_exist)
			DrawRect(r[i]);
	}
	for (int i = 0; i < disappear; ++i) {
		if (r_d[i].is_exist)
			DrawRect(r_d[i]);
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
		for (int i = 0; i < 5; ++i) {
			if (r[i].is_exist) {
				if (Conflict(r[i], x, y)) {
					// 사각형 사라지게
					r[i].is_exist = false;

					// 랜덤적으로
					int rand_num = 1;
					// 대각선
					if (rand_num == 0) {
						// 나누기, 타이머 함수
						for (int j = 0; j < 4; ++j) {
							ResetDisRect(r[i], 4);
							CrossReplaceDisRect(i, j);
							if (!start_cross) {
								start_cross = true;
								glutTimerFunc(100, TimerFunction, 1);
							}
						}
					}
					// 좌우상하 이동
					else if (rand_num == 1) {
						for (int j = 0; j < 4; ++j) {
							ResetDisRect(r[i], 4);
							UpDownReplaceDisRect(i, j);
							if (!start_updown) {
								start_updown = true;
								glutTimerFunc(100, TimerFunction, 2);
							}
						}
					}
					// 좌우상하대각선
					else if (rand_num == 2) {
						ResetDisRect(r[i], 8);
					}
				}
			}
		}
		glutPostRedisplay();
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		glutDestroyWindow(winID);
		std::cout << "프로그램 종료" << std::endl;
		break;
	}
}

GLvoid TimerFunction(int value)
{
	if (value == 1) {
		for (int i = 0; i < disappear; ++i) {
			MoveRect(r_d[i]);
		}
		glutTimerFunc(100, TimerFunction, 1);
	}
	else if (value == 2) {
		for (int i = 0; i < disappear; ++i) {
			MoveRect(r_d[i]);
		}
		glutTimerFunc(100, TimerFunction, 2);
	}

	glutPostRedisplay();
}