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
	glm::vec2 m_prev_mousePos{ glm::vec2(0.0f) };
	// x, 
	float m_camera_pitch{ 0.0f };
	// y
	float m_camera_yaw{ 0.0f };
	glm::vec3 m_camera_front{ glm::vec3(0.0f, -1.0f, 0.0f) };
	glm::vec3 m_camera_pos{ glm::vec3(0.0f, 0.0f, 3.0f) };
	glm::vec3 m_camera_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
public:
	CContext();
	~CContext();
public:
	void Init();
	void Render();
	void Update();
};

