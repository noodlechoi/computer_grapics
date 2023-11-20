#pragma once
#include "opengl_class/header.h"

// 텍스트 파일에 있는 버텍스를 읽는
class CReadObj
{
private:
	std::ifstream m_file;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_v_index_buff; // faces
	std::vector<glm::vec3> m_vn_index_buff; // faces
public:
	CReadObj();
	~CReadObj();
public:
	bool read_obj(std::string_view name);
};

