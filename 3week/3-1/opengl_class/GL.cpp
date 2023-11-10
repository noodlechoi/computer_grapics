#include "GL.h"
#include "header.h"

CGL::CGL()
{
	// initWindow���� ����
}

CGL::~CGL()
{

}

void CGL::initWindow(int argc, char** argv, const int& x, const int& y, std::string_view name)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(x, y);
	glutCreateWindow(name.data());


	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "glew �ʱ�ȭ ����" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "glew �ʱ�ȭ ���� " << std::endl;
}

