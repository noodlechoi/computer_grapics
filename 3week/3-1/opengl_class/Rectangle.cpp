#include "Rectangle.h"

CRectangle::CRectangle() : CFigure()
{
}

CRectangle::CRectangle(const float& pivot, const float& size, const std::array<float, 3>& color) : CFigure(pivot, size, color), sizes{size, size}
{
	// 각 꼭짓점에 동일한 색상 넣기
	for (int i = 0; i < 4; ++i) {
		this->colors[i] = { color[0],  color[1], color[2] };
	}
}

CRectangle::~CRectangle()
{
}

std::array<std::array<float, 4>, 3> CRectangle::getPos() const
{
	float w = sizes.first / 2;
	float h = sizes.second / 2;

	// LT, LB, RB, RT
	return {
		pivot - w, pivot + h, 1.0,
		pivot - w, pivot - h, 1.0,
		pivot + w, pivot - h, 1.0,
		pivot + w, pivot + h, 1.0,
	};
}

unsigned int CRectangle::getSizeOf() const
{
	return sizeof(float) * 4;
}

std::array<std::array<float, 4>, 3> CRectangle::getColor() const
{
	return this->colors;
}
