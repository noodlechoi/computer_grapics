#include <iostream>
#include <ctime>
#include <cmath>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

int winID;
bool start_timer;

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	winID = glutCreateWindow("실습 1"); // 윈도우 생성(윈도우 이름)

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
	// 초기 화면 흰색으로
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}

/*
화면에 800 x 600 크기의 윈도우를 띄운다.
 초기 배경색은 흰색
 윈도우를 띄우고 배경색을 키보드 입력에 따라 다양하게 적용 해 보기
 키보드 입력 값:
 c: 청록색 (초록 + 파랑)
 m: 자홍색 (빨강 + 파랑)
 y: 노랑색 (빨강 + 초록)
 a: 렌덤색
 w: 백색
 k: 검정색
 t: 타이머를 설정하여 특정 시간마다 렌덤색으로 계속 바뀌게 한다.
 s: 타이머 종료
 q: 프로그램 종료
*/

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{ 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		break;
	case 'm':
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		break;
	case 'y':
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 'a':
	{
		double rand_num[] = { fmod(rand(), 0.9f), fmod(rand(), 0.9f), fmod(rand(), 0.9f) };
		glClearColor(rand_num[0], rand_num[1], rand_num[2], 1.0f);
	}
		break;
	case 'w':
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 'k':
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 't':
		start_timer = true;
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 's':
		start_timer = false;
		break;
	case 'q':
		glutDestroyWindow(winID);
		std::cout << "프로그램 종료" << std::endl;
		break;
	}

	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다, 호출 시 drawScene로 이동한다!
}

GLvoid TimerFunction(int value)
{
	// s 입력 시 함수 탈출
	if (!start_timer)
		return;
	
	double rand_num[] = { fmod(rand(), 0.9f), fmod(rand(), 0.9f), fmod(rand(), 0.9f) };
	glClearColor(rand_num[0], rand_num[1], rand_num[2], 1.0f);

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}