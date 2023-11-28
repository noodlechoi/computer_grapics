#pragma once
#include "header.h"
#include "header_user.h"
#include "Model.h"

class CContext
{
private:
	CShader* m_program;
	//CModel m_model;
	std::vector<CMesh*>m_meshes;

	// object
	float m_obj_radian_x{ 0.0f };
	float m_obj_radian_y{ 0.0f };

	// camera parameter
	bool m_camera_control{ false };
	
	// camera front ���� ���� ����
	float m_camera_pitch{ -25.0f }; // x��
	float m_camera_yaw{ 25.0f }; // y��
	// roll ��� up vector�� ��Ʈ��

	glm::vec3 m_camera_pos{ glm::vec3(3.0f, 3.0f, 7.0f) };
	glm::vec3 m_camera_front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 m_camera_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec2 m_prev_pos{ glm::vec2(0.0f, 0.0f) };

	// light
	glm::vec3 radius = { glm::vec3(2.0f, 0.0f, 0.0f) };

	//glm::vec3 m_light_pos{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 m_light_color{ glm::vec3(1.0f, 1.0f, 1.0f) };
	glm::vec3 m_object_color{ glm::vec3(1.0f, 0.5f, 0.0f) };
	float m_ambient_strength{ 0.1f };
	float m_spec_strength{ 0.5f };
	float m_spec_shininess{ 32.0f };

	// �ǽ� Ű �Է� flag
	bool n_flag = false;
	bool m_flag = false;
	bool y_flag = false;
	bool r_flag = false;

	// ��ü ��ȯ ����
	float m_light_obj_y{ 0.0f };

public:
	CContext();
	~CContext();
public:
	void Init();
	void KeyBoard(const unsigned char& key, const int& x, const int& y);
	void Mouse(const int& button, const int& state, const int& x, const int& y);
	void Motion(const int& x, const int& y);
	void Time(int value);
	void Render();
	void Update();
};

