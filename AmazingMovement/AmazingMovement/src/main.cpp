#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "t: ������ �Ҵ�/����" << endl;
	cout << "c: ���� ���� �ٲ۴�. �ּ� 3���� �ٸ� ���� �����غ���." << endl;
	cout << "y/Y: ī�޶� �ٴ��� y���� �������� ��/�� �������� ȸ���Ѵ�. (����, �ٽ� ������ ȸ���� �����Ѵ�.)" << endl;
	cout << "+/-: ����ü �̵��ϴ� �ӵ� ����/����" << endl;
	cout << "1: �������� �Դٰ�����" << endl;
	cout << "2: �ĵ� Ÿ��" << endl;
	cout << "3: ���ó�� �Դٰ�����" << endl;
	cout << "r: ��� �� �ʱ�ȭ" << endl;
	cout << "q : ���α׷� ����" << endl;
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
