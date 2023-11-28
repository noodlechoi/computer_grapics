#include "Rectangle.h"

CRectangle::CRectangle()
{
}

CRectangle::CRectangle(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color) : sizes{m_size, m_size}
{
	tris[0].Set(m_pivot, m_size, m_color);
	tris[1].Set(m_pivot, m_size, m_color);
}

CRectangle::~CRectangle()
{
}

std::array<std::array<float, 3>, 6> CRectangle::GetPos() const
{
	float w = sizes.first / 2;
	float h = sizes.second / 2;

	std::pair<float, float> p = tris[0].GetPivot();

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

unsigned int CRectangle::GetSizeof() const
{
	return sizeof(float) * 3 * 6;
}

std::array<std::array<float, 3>, 6> CRectangle::GetColor() const
{
	const std::array<std::array<float, 3>, 3> color0 = tris[0].GetColor();
	const std::array<std::array<float, 3>, 3> color1 = tris[1].GetColor();

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

void CRectangle::setSizes(const std::pair<float, float>& m_size)
{
	this->sizes = m_size;
}
