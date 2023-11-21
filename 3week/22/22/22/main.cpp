#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "o / O: 앞면이 좌우로 열린다." << endl;
	cout << "w/a/s/d: 로봇이 앞/뒤/좌/우 방향으로 이동 방향을 바꿔서 걷는다. 가장자리에 도달하면 로봇은 뒤로 돌아 다시 걷는다" << endl;
	cout << "+/-: 걷는 속도가 빨라지거나/느려진다." << endl;
	cout << "j: 로봇이 제자리에서 점프한다." << endl;
	cout << "i: 모든 변환을 리셋하고 다시 시작" << endl;
	cout << "z/Z: 앞뒤로 이동" << endl;
	cout << "x/X: 좌우로 이동" << endl;
	cout << "y/Y: 카메라가 현재 위치에서 화면 중심 y축을 기준으로 공전" << endl;
}

void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

int main(int argc, char** argv)
{
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "실습 22");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// 깊이 검사 설정
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	PrintKey();
	while (1) {

		glutKeyboardFunc(KeyBoard);
		glutMouseFunc(Mouse);
		glutMotionFunc(Motion);
		glutMainLoop();
	}
	// 깊이 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

