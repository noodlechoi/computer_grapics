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
	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "Ω«Ω¿ 22");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// ±Ì¿Ã ∞ÀªÁ º≥¡§
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	while (1) {

		glutPostRedisplay();
		context.Update();
		glutMainLoop();
	}
	// ±Ì¿Ã 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

