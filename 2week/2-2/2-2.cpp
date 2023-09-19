#include <iostream>
#include <ctime>
#include <cmath>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct Rect
{
	GLfloat x1, y1, x2, y2;
}Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

int winID;

// 내부 : 0 ~ 3, 외부 : 4 ~ 7
Rect r[8];
double color[8][3];

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 2"); // 윈도우 생성(윈도우 이름)

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

	// 사각형 좌표 배열 초기화, 원도우 중심을 원점으로 하여 사분면 계산
	for (int i = 0; i < 8; ++i) {
		if (i % 4 == 0)
			r[i] = {0, 0, WIDTH / 2, HEIGHT / 2};
		else if(i % 4 == 1)
			r[i] = { 0, 0, -WIDTH / 2, HEIGHT / 2 };
		else if (i % 4 == 2)
			r[i] = { 0, 0, -WIDTH / 2, -HEIGHT / 2 };
		else if (i % 4 == 3)
			r[i] = { 0, 0, WIDTH / 2, -HEIGHT / 2 };
		// 색깔 설정
		for (int j = 0; j < 3; ++j)
			color[i][j] = fmod(rand(), 0.9f);
	}

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
윈도우를 띄우고 마우스 명령을 실행 해 본다.
 화면의 가로 세로를 각각 2등분하여 사각형 4개를 그린다.
 네 개의 사각형에 마우스를 클릭하여 색상과 크기를 바꾼다.
 왼쪽 마우스 클릭
 사각형 내부 클릭: 사각형 색상을 랜덤하게 바꾸기
 사각형 외부 클릭: 배경색을 랜덤하게 바꾸기
 오른쪽 마우스 클릭
 사각형 내부 클릭: 사각형 크기 축소
 사각형 외부 클릭: 사각형 크기 확대
=> 사각형 하나 더 위에 만들기
 사각형 그리기 함수
 void glRectf (Glfloat x1, Glfloat y1, Glfloat x2, Glfloat y2);
 (x1, y1): 좌측 하단 좌표값
 (x2, y2): 우측 상단 좌표값
 사각형 색상 바꾸기
 void glColor3f (Glfloat r, Glfloat g, Glfloat b);
 현재 색상 설정하기
 (r, g, b): red, green, blue 색상, 0.0 ~ 1.0 사이의 값으로 glRectf 를 호출하기 직전 설정한다.
** Modern openGL 에서는 사용할 수 없는 deprecated 함수
** 셰이더를 사용하게 되면 이 함수는 사용할 수 없음
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	for (int i = 0; i < 8; ++i) {
		// 사각형 생성
		glRectf(r[i].x1, r[i].y1, r[i].x2, r[i].y2);
		// 사각형 색깔 설정
		glColor3f(color[i][0], color[i][1], color[i][2]);
	}

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	// 만약 내부에 있는 사각형이 먼저 충돌 됐으면 외부 사각형은 비교 X
	if (button == GLUT_LEFT_BUTTON) {
		// 내부 사각형
		for (int i = 0; i < 8; ++i) {

		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {

	}

}