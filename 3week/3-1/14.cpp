#include "header.h"
#include "opengl_class\header_user.h"

CVAO vao;
std::vector<CVBO> vbos;
CShader shader("vertex.glsl", "fragment.glsl");

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid initBuffer();

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	CGL::GetInstance()->initWindow(argc, argv, WIDTH, HEIGHT, "실습 14");

	shader.makeShaderProgram();
	initBuffer();
	// 깊이 검사 설정
	//glEnable(GL_DEPTH_TEST);

	// 루프 (콜백함수)
	glutDisplayFunc(drawScene);
	//glutMouseFunc(Mouse);
	//glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	// 깊이 
	//glDisable(GL_DEPTH_TEST);
}

/*
3차원 객체, 육면체 또는 사면체의 면을 명령어에 따라 그리기
 모든 객체들은 X축으로 10도, y축으로 10도 회전해서 그린다. (3차원 도형이라 약간 기울어지게 그린다)
 다음의 키보드 명령어에 따라 도형을 구성하는 각 면을 그린다. 각 면마다 색상을 정해 해당 색상으로 그린다.
 1/2/3/4/5/6: 육면체의 각 면을 그린다.
 7/8/9/0 : 사면체의 각 면을 그린다.
 c: 육면체에서 랜덤한 2개의 면을 그린다.
 t: 사면체에서 랜덤한 2개의 면을 그린다.
*/

//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid drawScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 사용할 VAO 불러오기
	vao.Bind();

	int PosLocation = shader.getLocation("in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = shader.getLocation("in_Color"); //	: 1
	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);

	// 좌표축 그리기
	vbos[0].Bind();
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	vbos[1].Bind();
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;
	case '9':
		break;
	case '0':
		break;
	case 'c':
		break;
	case 't':
		break;
	default:
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{

}

GLvoid initBuffer()
{
	vao.Gen();

	const GLfloat line[2][3] = {
		{-1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}
	};
	const GLfloat color[2][3] = {
		{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}
	};

	vbos.push_back(CVBO(line, sizeof(line)));
	vbos.push_back(CVBO(color, sizeof(color)));

}