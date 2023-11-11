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
	CRectangle(const std::pair<float, float>& pivot, const float& size, const std::array<float, 3>& color);
	~CRectangle();
public:
	std::array<std::array<float, 3>, 6> getPos() const;
	unsigned int getSizeOf() const;
	std::array<std::array<float, 3>, 6> getColor() const;
	void setSizes(const std::pair<float, float>& size);
};

