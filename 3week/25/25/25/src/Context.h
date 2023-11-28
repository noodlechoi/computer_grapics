#pragma once
#include "header.h"
#include "header_user.h"
#include "Model.h"

class CContext
{
private:
	CShader* m_program;
	//CModel m_model;
	CMesh* m_box;
	std::vector<CMesh*>m_meshes;

	// object
	float m_obj_radian_x{ 0.0f };
	float m_obj_radian_y{ 0.0f };

	// camera parameter
	bool m_camera_control{ false };
	
	// camera front 방향 결정 각도
	float m_camera_pitch{ 0.0f }; // x축
	float m_camera_yaw{ 0.0f }; // y축
	// roll 대신 up vector로 컨트롤

	glm::vec3 m_camera_pos{ glm::vec3(0.0f, 0.0f, 10.0f) };
	glm::vec3 m_camera_front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 m_camera_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec2 m_prev_pos{ glm::vec2(0.0f, 0.0f) };

	// light parameter
	struct Light {
		glm::vec3 position{ glm::vec3(2.0f, 0.0f, 0.0f) };
		glm::vec3 ambient{ glm::vec3(0.1f, 0.1f, 0.1f) };
		glm::vec3 diffuse{ glm::vec3(0.5f, 0.5f, 0.5f) };
		glm::vec3 specular{ glm::vec3(1.0f, 1.0f, 1.0f) };
	};
	Light m_light;

	// material parameter
	struct Material {
		glm::vec3 ambient{ glm::vec3(1.0f, 0.5f, 0.3f) };
		glm::vec3 diffuse{ glm::vec3(1.0f, 0.5f, 0.2f) };
		glm::vec3 specular{ glm::vec3(1.0f, 1.0f, 1.0f) };
		float shininess{ 32.0f };
	};
	Material m_material;
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

