#pragma once
#include "Figure.h"

class CTriangle : public CFigure
{
protected:
	std::array<std::array<float, 3>, 3> colors;
public:
	CTriangle();
	CTriangle(const float& pivot, const float& size, const std::array<float, 3>& color);
	~CTriangle();
public:
	std::array<std::array<float, 3>, 3> getPos() const;
	unsigned int getSizeOf() const;
	std::array<std::array<float, 3>, 3> getColor() const;
	void set(const float& pivot, const float& size, const std::array<float, 3>& color) override;
};
