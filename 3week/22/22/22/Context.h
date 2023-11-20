#pragma once
#include "opengl_class/header.h"
#include "opengl_class/header_user.h"

class CContext
{
private:
	CShader* m_program;
	CVAO* m_vao;
	CBuffer* m_vertexbuffer;
	CBuffer* m_indexbuffer;

	// camera parameter
	bool m_camera_control{ false };
	
	// camera front 방향 결정 각도
	float m_camera_pitch{ 0.0f }; // x축
	float m_camera_yaw{ 0.0f }; // y축
	// roll 대신 up vector로 컨트롤

	glm::vec3 m_camera_pos{ glm::vec3(0.0f, 0.0f, 3.0f) };
	glm::vec3 m_camera_front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 m_camera_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
public:
	CContext();
	~CContext();
public:
	void Init();
	void KeyBoard(const unsigned char& key, const int& x, const int& y);
	void Mouse(const int& button, const int& state, const int& x, const int& y);
	void Motion(const int& x, const int& y);
	void Render();
	void Update();
};

