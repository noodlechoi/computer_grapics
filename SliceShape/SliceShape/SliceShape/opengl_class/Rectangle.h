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
	CRectangle(const std::pair<float, float>& pivot, const float& size, const std::array<float, 3>& color);
	~CRectangle();
public:
	std::array<std::array<float, 3>, 6> getPos() const;
	unsigned int getSizeOf() const;
	std::array<std::array<float, 3>, 6> getColor() const;
	void setSizes(const std::pair<float, float>& size);
};

