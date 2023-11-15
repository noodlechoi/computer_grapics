#pragma once
#include "Triangle.h"

// �ﰢ�� 2���� �ִ� �簢�� ��ü
class CRectangle
{
protected:
	std::array<CTriangle, 2> tris;
	std::pair<float, float> sizes;
public:
	CRectangle();
	CRectangle(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color);
	~CRectangle();
public:
	std::array<std::array<float, 3>, 6> GetPos() const;
	unsigned int GetSizeof() const;
	std::array<std::array<float, 3>, 6> GetColor() const;
	void setSizes(const std::pair<float, float>& m_size);
};

