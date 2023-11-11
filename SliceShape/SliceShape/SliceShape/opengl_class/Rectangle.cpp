#include "Rectangle.h"

CRectangle::CRectangle()
{
}

CRectangle::CRectangle(const std::pair<float, float>& pivot, const float& size, const std::array<float, 3>& color) : sizes{size, size}
{
	tris[0].set(pivot, size, color);
	tris[1].set(pivot, size, color);
}

CRectangle::~CRectangle()
{
}

std::array<std::array<float, 3>, 6> CRectangle::getPos() const
{
	float w = sizes.first / 2;
	float h = sizes.second / 2;

	std::pair<float, float> p = tris[0].getPivot();

	// LT, LB, RB, LB, RB, RT
	return {
		p.first - w, p.second + h, 1.0,
		p.first - w, p.second - h, 1.0,
		p.first + w, p.second + h, 1.0,
		p.first - w, p.second - h, 1.0,
		p.first + w, p.second - h, 1.0,
		p.first + w, p.second + h, 1.0,
	};
}

unsigned int CRectangle::getSizeOf() const
{
	return sizeof(float) * 3 * 6;
}

std::array<std::array<float, 3>, 6> CRectangle::getColor() const
{
	const std::array<std::array<float, 3>, 3> color0 = tris[0].getColor();
	const std::array<std::array<float, 3>, 3> color1 = tris[1].getColor();

	return {
		color0[0][0],
		color0[0][1],
		color0[0][2],
		color0[1][0],
		color0[1][1],
		color0[1][2],
		color0[2][0],
		color0[2][1],
		color0[2][2],

		color1[0][0],
		color1[0][1],
		color1[0][2],
		color1[1][0],
		color1[1][1],
		color1[1][2],
		color1[2][0],
		color1[2][1],
		color1[2][2],
	};
}

void CRectangle::setSizes(const std::pair<float, float>& size)
{
	this->sizes = size;
}
