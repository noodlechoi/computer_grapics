#include "Triangle.h"

CTriangle::CTriangle() : CFigure()
{
}

CTriangle::CTriangle(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color) : CFigure(m_pivot, m_size, m_color)
{
	// 각 꼭짓점에 동일한 색상 넣기
	for (int i = 0; i < 3; ++i) {
		this->colors[i] = { m_color[0],  m_color[1], m_color[2] };
	}
}

CTriangle::~CTriangle()
{
}

std::array<std::array<float, 3>, 3> CTriangle::GetPos() const
{
	// pivot으로 부터 차이
	// 가로 : size / 2
	// 세로 : (가로) / tan30
	
	float width = m_size / 2;
	float height = width / tan(toRadian(30));
	

	// 반시계 방향으로 반환
	// 왼쪽, 오른쪽 위
	return { m_pivot.first - width, m_pivot.second - height, 1.0f, {m_pivot.first + width, m_pivot.second - height, 1.0f}, {m_pivot.first, m_pivot.second + height, 1.0f} };
}

unsigned int CTriangle::GetSizeof() const
{
	return sizeof(float) * 9;
}

std::array<std::array<float, 3>, 3> CTriangle::GetColor() const
{
	return this->colors;
}

void CTriangle::Set(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color)
{
	CFigure::Set(m_pivot, m_size, m_color);

	for (int i = 0; i < 3; ++i) {
		this->colors[i] = { m_color[0],  m_color[1], m_color[2] };
	}
}
