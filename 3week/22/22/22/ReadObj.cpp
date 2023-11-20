#include "ReadObj.h"

CReadObj::CReadObj()
{
}

CReadObj::~CReadObj()
{
}

bool CReadObj::read_obj(std::string_view name)
{
	m_file.open(name.data());

    if (!m_file.is_open()) {
        std::cout << "������ �� �� �����ϴ�." << std::endl;
        return false;
    }

    std::string line;

    // �� �پ� �б�
    while (std::getline(m_file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { // ���� ������ ���
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            m_vertices.push_back(vertex);
        }
        else if (prefix == "vn") { // ���� ������ ���
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            m_normals.push_back(normal);
        }
        else if (prefix == "f") { // �� ������ ���
            glm::vec3 v_index_buff, vn_index_buff;

            iss >> v_index_buff.x;
            iss.ignore(2); // ������ �ǳʶٱ�
            iss >> vn_index_buff.x;

            iss >> v_index_buff.y;
            iss.ignore(2);
            iss >> vn_index_buff.y;

            iss >> v_index_buff.z;
            iss.ignore(2);
            iss >> vn_index_buff.z;

            m_v_index_buff.push_back(v_index_buff);
            m_vn_index_buff.push_back(vn_index_buff);
        }
    }

    m_file.close();

    return true;
}
