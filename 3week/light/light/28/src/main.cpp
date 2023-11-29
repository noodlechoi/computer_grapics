#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "s: 하늘에서 눈이 내린다." << endl;
	cout << "0~5: 시어핀스키 프렉탈 삼각형의 단계" << endl;
	cout << "r: 조명이 화면 중앙의 y축에 대하여 공전한다/멈춘다. " << endl;
	cout << "n/f: 조명이 가까워지기/멀어지기" << endl;
	cout << "+/-: 조명의 세기 높아지기/낮춰지기" << endl;
	cout << "q : 프로그램 종료" << endl;
}

void DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.Update();
	context.Render();
	glutSwapBuffers();
}

void KeyBoard(unsigned char key, int x, int y)
{
	context.KeyBoard(key, x, y);
}

void Mouse(int button, int state, int x, int y)
{
	context.Mouse(button, state, x, y);
}

void Motion(int x, int y)
{
	context.Motion(x, y);
}

void Time(int value)
{
	context.Time(value);
	glutTimerFunc(100, Time, 1);
}

int main(int argc, char** argv)
{
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "실습 28");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// 깊이 검사 설정
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	PrintKey();

	glutKeyboardFunc(KeyBoard);
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutTimerFunc(100, Time, 1);
	glutMainLoop();

	// 깊이 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

