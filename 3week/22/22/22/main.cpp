#include "Context.h"

CContext context;

void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.Render();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "�ǽ� 22");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// ���� �˻� ����
	//glEnable(GL_DEPTH_TEST);
	while (1) {

		context.Update();
		glutPostRedisplay();
		glutMainLoop();
	}
	// ���� 
	//glDisable(GL_DEPTH_TEST);
}

