#pragma once
#include "header.h"

// �ؽ�Ʈ ���Ͽ� �ִ� ���ؽ��� �д�
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
	bool ReadObj(std::string_view name);
	std::vector<glm::vec3> GetVertex();
	std::vector<glm::vec3> GetNormal();
	std::vector<glm::vec3> GetVertexBuff();
	std::vector<glm::vec3> GetNormalBuff();
};

