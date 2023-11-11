#include "GL.h"
#include "header.h"

CGL::CGL()
{
	// initWindow에서 생성
}

CGL::~CGL()
{

}

void CGL::initWindow(int argc, char** argv, const int& x, const int& y, std::string_view name)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(x, y);
	glutCreateWindow(name.data());


	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "glew 초기화 실패" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "glew 초기화 성공 " << std::endl;
}

