#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "n: 육면체 / 사각뿔 그리기" << endl;
	cout << "m : 조명 켜기 / 끄기" << endl;
	cout << "y : 객체를 y축에 대하여 회전(제자리에서 자전)" << endl;
	cout << "r : 조명을 객체의 중심 y축에 대하여 양 / 음 방향으로 공전시키기" << endl;
	cout << "z / Z : 조명을 객체에 가깝게 / 멀게 이동하기" << endl;
	cout << "q : 프로그램 종료" << endl;
	cout << "조명의 공전 궤도를 원으로 그린다." << endl;
	cout << "조명의 위치가 바뀌게 되면 공전 궤도의 크기도 같이 바뀐다." << endl;
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
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "실습 25");
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

