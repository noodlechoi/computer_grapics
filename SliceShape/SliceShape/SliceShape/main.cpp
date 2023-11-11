#include "opengl_class\header.h"
#include "opengl_class\header_user.h"
#include "Random.h"

CVAO vao;
std::vector<CVBO> vbos;
std::vector<std::pair<std::array<float, 2>, int>> trans;
bool is_right;
CRandom rand_num;
CShader shader("vertex.glsl", "fragment.glsl");

Point ConvertPoint(const int& x, const int& y, const int& window_width, const int& window_height)
{
	Point tmp;
	tmp.x = (double)((x - (double)window_width / 2.0) * (double)(1.0 / (double)(window_width / 2.0)));
	tmp.y = -(double)((y - (double)window_height / 2.0) * (double)(1.0 / (double)(window_height / 2.0)));

	return tmp;
}

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
GLvoid initBuffer();

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	CGL::GetInstance()->initWindow(argc, argv, WIDTH, HEIGHT, "SliceShape");

	shader.makeShaderProgram();
	initBuffer();

	// 루프 (콜백함수)
	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(1000, TimerFunction, 2); // 타이머함수 재 설정
	glutReshapeFunc(Reshape);
	glutMainLoop();

}

/*
* 날라오는 도형을 슬라이스 하기
• 화면의 좌측, 또는 우측 가장자리의 임의의 위치에서 도형이 화면의 반대편으로 날라온다
• 날라오는 경로: 사선으로 설정한다. 
• 도형의 종류: 삼각형 이상의 면을 가지고 있는 2 종류 이상의 도형 (최소 삼각형과 사각형) 
• 아래에는 바구니가 좌우로 움직이고 있다.
• 마우스를 클릭, 드래그하여 도형을 슬라이스 한다. 
• 도형이 잘려서 작은 조각이 되어 아래로 떨어진다. 
• 조각이 떨어질 때는 중력이 적용되어 떨어진다. 
• 떨어진 조각이 바구니에 닿으면 바구니 위에 놓여져 있다.
• 슬라이스 하지 못하면 반대편으로 사라진다.
• 종료 명령어가 입력될 때까지 계속 도형이 날라온다.
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


	// bar
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(trans[0].first[0], trans[0].first[1], 0.0f));
	unsigned int modelLocation = shader.getUniform("transform");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	for (int i = 0; i < 2; ++i) {

		vbos[0].Bind();
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * 9 * i));
		vbos[1].Bind();
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * 9 * i));

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// 날라오는 도형들

	int trans_idx = 1;
	for (int i = 2; i < vbos.size(); ) {
		if (trans_idx + 1 > trans.size()) break;

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(trans[trans_idx].first[0], trans[trans_idx].first[1], 0.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		// 삼각형
		if (vbos[i].getType() == static_cast<unsigned int>(EShape::tri)) {
			vbos[i].Bind();
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			vbos[i + 1].Bind();
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			vbos[i].draw();
		}
		// 사각형
		else {
			for (int j = 0; j < 2; ++j) {
				vbos[i].Bind();
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * 9 * j));
				vbos[i + 1].Bind();
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * 9 * j));
				vbos[i].draw();
			}
		}

		// 2개씩
		if (i > vbos.size()) break;
		i += 2;
		trans_idx++;
	}

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);

	glutSwapBuffers(); //--- 화면에 출력하기
}
/*
* 도형의 모드: LINE/FILL 
• 경로 출력하기: on/off 
• 날라오는 속도 변경하기: +/- (빨라지기/느려지기) 
• 프로그램 종료: q
*/
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
	case 'L':
		break;
	case 'p':
		break;
	case '+':
		break;
	case '-':
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Point p = ConvertPoint(x, y, WIDTH, HEIGHT);
		std::cout << p.x << " " << p.y << std::endl;
	}

}

void TimerFunction(int value)
{
	// 움직이는 타이머
	if (value == 1) {
		// bar 움직이기
		trans[0].first[0] += 0.1f * trans[0].second;
		if (trans[0].first[0] >= 0.8) trans[0].second = -1;
		if (trans[0].first[0] <= -0.8) trans[0].second = 1;
		// 날아다니는 도형 움직이기
		for (int i = 1; i < trans.size(); ++i) {
			trans[i].first[0] += 0.08f * trans[i].second;
			// 무조건 아래로
			trans[i].first[1] += 0.1f * -1;

			// 바닥으로 가면 사라짐
			if (trans[i].first[1] <= -3.0) {
				trans.erase(trans.begin() + i);
				vbos.erase(vbos.begin() + (2 * i));
				vbos.erase(vbos.begin() + (2 * i + 1));
				i--;
			}
		}
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
	}
	// 생성 타이머
	if (value == 2) {
		size_t rand_type = rand_num.get(static_cast<size_t>(EShape::tri), static_cast<size_t>(EShape::rec));
		//size_t rand_type = static_cast<size_t>(EShape::tri);

		std::array<float, 2> rand_pos = { 1.0, rand_num.get(0.0f, 0.2f) };
		std::array<float, 3> rand_color = { rand_num.get(0.0f, 0.5f) + 0.4f, rand_num.get(0.0f, 0.5f) + 0.4f, rand_num.get(0.0f, 0.5f) + 0.4f };

		// 왼쪽으로 생성 위치 변경
		if (!is_right) {
			rand_pos[0] = -1.0f;
			is_right = true;
		}
		else {
			rand_pos[0] = 1.0f;
			is_right = false;
		}

		// 삼각형 생성
		if (rand_type == static_cast<size_t>(EShape::tri)) {
			CTriangle tri({ rand_pos[0], rand_pos[1] + 0.6}, 0.2, rand_color);
			vbos.push_back(CVBO(tri.getPos().data(), tri.getSizeOf(), static_cast<unsigned int>(EShape::tri)));
			vbos.push_back(CVBO(tri.getColor().data(), tri.getSizeOf(), static_cast<unsigned int>(EShape::tri)));
		}
		// 사각형 생성
		else {
			CRectangle rec({ rand_pos[0], rand_pos[1] + 0.6 }, 0.2, rand_color);
			vbos.push_back(CVBO(rec.getPos().data(), rec.getSizeOf(), static_cast<unsigned int>(EShape::rec)));
			vbos.push_back(CVBO(rec.getColor().data(), rec.getSizeOf(), static_cast<unsigned int>(EShape::rec)));
		}

		// 오른쪽이면 왼쪽으로
		if (rand_pos[0] == 1.0) {
			trans.push_back({ { 0.0, 0.0 }, -1 });
		}
		else {
			trans.push_back({ { 0.0, 0.0 }, 1 });
		}
		glutTimerFunc(1000, TimerFunction, 2); // 타이머함수 재 설정
	}

	glutPostRedisplay(); // 화면 재 출력
}

GLvoid initBuffer()
{
	vao.Gen();

	CRectangle bar({0.0, -0.8}, 0.2, {0.0, 1.0, 0.0});
	bar.setSizes({ 0.4, 0.1 });
	
	vbos.push_back(CVBO(bar.getPos().data(), bar.getSizeOf(), static_cast<unsigned int>(EShape::rec)));
	vbos.push_back(CVBO(bar.getColor().data(), bar.getSizeOf(), static_cast<unsigned int>(EShape::rec)));

	trans.push_back({ { 0.0, 0.0 }, 1 });
}