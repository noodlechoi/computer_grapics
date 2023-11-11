#pragma once
#include "Figure.h"

class CRectangle : public CFigure
{
protected:
	std::pair<float, float> sizes;
	std::array<std::array<float, 4>, 3> colors;
public:
	CRectangle();
	CRectangle(const float& pivot, const float& size, const std::array<float, 3>& color);
	~CRectangle();
public:
	std::array<std::array<float, 4>, 3> getPos() const;
	unsigned int getSizeOf() const;
	std::array<std::array<float, 4>, 3> getColor() const;
};

