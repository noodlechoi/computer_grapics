#include "Context.h"

CContext context;

void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "�ǽ� 22");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// ���� �˻� ����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	while (1) {

		glutPostRedisplay();
		context.Update();
		glutKeyboardFunc(KeyBoard);
		glutMouseFunc(Mouse);
		glutMotionFunc(Motion);
		glutMainLoop();
	}
	// ���� 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

