#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "c: 조명 색을 다른 색으로 바뀌도록 한다. 3종류의 다른 색을 적용해본다." << endl;
	cout << "r/R: 조명의 위치를 중심의 구의 y축에 대하여 양/음 방향으로 회전한다." << endl;
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
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "실습 26");
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

