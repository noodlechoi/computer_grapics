#include "Figure.h"

CFigure::CFigure() : m_pivot{0.0, 0.0}, m_color{0.0, 0.0, 0.0}, m_size{1.0}
{

}


CFigure::CFigure(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color) : m_pivot{m_pivot}, m_size{m_size}, m_color{m_color}
{
}

CFigure::~CFigure()
{
}

std::pair<float, float> CFigure::GetPivot() const
{
	return this->m_pivot;
}

float CFigure::GetSize() const
{
	return this->m_size;
}

std::array<float, 3> CFigure::GetColor() const
{
	return this->m_color;
}

void CFigure::Set(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color)
{
	this->m_pivot = m_pivot;
	this->m_size = m_size;
	this->m_color = m_color;
}

