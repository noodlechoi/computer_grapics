#pragma once
#include "Triangle.h"

// 삼각형 2개가 있는 사각형 객체
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

