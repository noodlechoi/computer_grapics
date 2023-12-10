#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "t: 조명을 켠다/끈다" << endl;
	cout << "c: 조명 색을 바꾼다. 최소 3개의 다른 색을 적용해본다." << endl;
	cout << "y/Y: 카메라가 바닥의 y축을 기준으로 양/음 방향으로 회전한다. (공전, 다시 누르면 회전을 중지한다.)" << endl;
	cout << "+/-: 육면체 이동하는 속도 증가/감소" << endl;
	cout << "1: 랜덤으로 왔다갔다함" << endl;
	cout << "2: 파도 타기" << endl;
	cout << "3: 계단처럼 왔다갔다함" << endl;
	cout << "r: 모든 값 초기화" << endl;
	cout << "q : 프로그램 종료" << endl;
}

void DrawScene()
{
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
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
	glutTimerFunc(context.GetSpeed(), Time, 1);
}

int main(int argc, char** argv)
{
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "Amazing Movement");
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

