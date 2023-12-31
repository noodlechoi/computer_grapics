#include "pch.h"
#include "Core.h"


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

Core::Core()
{
	//init 에서 처리함
}

Core::~Core()
{
}

void Core::Init(int argc, char** argv, int x, int y) //
{
	::glutInit(&argc, argv); // glut 초기화   GLUT와 openGL 환경 초기화
	::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 컬러모델, 윈도우 버퍼 등 초기의 출력 모드를 결정한다.
	::glutInitWindowPosition(0, 0); // 윈도우 시작 지점 (x,y)
	::glutInitWindowSize(x, y);  // 윈도우 크기 조정 
	::glutCreateWindow("my window");

	//--- GLEW 초기화하기
	::glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "glew 초기화 실패" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "glew 초기화 성공 " << std::endl;



}

void Core::Render(void (*funcptr)(void))
{
	::glutDisplayFunc(funcptr);
	::glutReshapeFunc(Reshape);

}

//void Core::Keyboard(void (*funcptr)(unsigned char, int, int))
//{
//	glutKeyboardFunc(funcptr);
//}
//
//void Core::mousein(void(*funcptr)(int button, int state, int x, int y))
//{
//	glutMouseFunc(funcptr);
//}
//
//void Core::mouse_move(void(*funcptr)(int x, int y))
//{
//	glutMotionFunc(funcptr);
//}

Pos Core::convert(int x, int y, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	int w = WINDOW_WIDTH;
	int h = WINDOW_HEIGHT;

	float ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	float oy = -((float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));

	Pos pos = { ox,oy };

	return pos;
}




