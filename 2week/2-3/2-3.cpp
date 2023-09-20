#include <iostream>
#include <ctime>
#include <cmath>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>



template <typename T>
class Rect
{
private:
	// 원점
	T x, y;
	double color[3];
	bool is_alive;
	T size;
public:
	Rect();
	void DrawRect();
	void Move(T x, T y);
};

template <typename T>
Rect<T>::Rect() : x{}, y{}, is_alive {}, size{0.1f}
{
	// 색 랜덤 색으로 초기화
	for (int i = 0; i < 3; ++i)
		color[i] = fmod(rand(), 0.9f);
}

template <typename T>
void Rect<T>::DrawRect()
{
	glRectf(x - size, y - size, x + size, y + size);
	glColor3f(color[0], color[1], color[2]);
}

template <typename T>
void Rect<T>::Move(T x, T y)
{
	this->x = x;
	this->y = y;
}

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int winID;
template <typename T>
Rect<T> r;

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 3"); // 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	// 랜덤 시드 설정
	srand((unsigned int)time(NULL));

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMainLoop(); // 이벤트 처리 시작
}

/*
사각형 이동하기
 화면 중앙에 사각형을 그린 후,
 마우스 버튼을 사각형 위에 클릭한 채로 드래그 하면
 사각형의 위치가 이동된다.
 마우스를 놓으면 더 이상 사각형이 이동하지 않는다.
 키보드를 눌러 사각형을 추가로 만든다.
 키보드 a: 화면의 랜덤한 위치에 다른 색상의 사각형을 만든다. 최대 5개 만든다. 새롭게 만든 사각형도 이동할 수 있다.
 사각형이 겹쳐져 있으면 나중에 만든 사각형이 위에 올라오고 그 사각형이 선택된다

사각형 클래스, 그것을 다루는 클래스 따로 만들기
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	r<double>.DrawRect();

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}