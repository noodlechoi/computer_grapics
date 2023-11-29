#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "s: �ϴÿ��� ���� ������." << endl;
	cout << "0~5: �þ��ɽ�Ű ����Ż �ﰢ���� �ܰ�" << endl;
	cout << "r: ������ ȭ�� �߾��� y�࿡ ���Ͽ� �����Ѵ�/�����. " << endl;
	cout << "n/f: ������ ���������/�־�����" << endl;
	cout << "+/-: ������ ���� ��������/��������" << endl;
	cout << "q : ���α׷� ����" << endl;
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
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "�ǽ� 28");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// ���� �˻� ����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	PrintKey();

	glutKeyboardFunc(KeyBoard);
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutTimerFunc(100, Time, 1);
	glutMainLoop();

	// ���� 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

