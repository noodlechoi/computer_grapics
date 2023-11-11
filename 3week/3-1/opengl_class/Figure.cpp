#include "Figure.h"

CFigure::CFigure() : pivot{0.0}, color{0.0, 0.0, 0.0}, size{1.0}
{

}


CFigure::CFigure(const float& pivot, const float& size, const std::array<float, 3>& color) : pivot{pivot}, size{size}, color{color}
{
}

CFigure::~CFigure()
{
}

float CFigure::getPivot() const
{
	return this->pivot;
}

float CFigure::getSize() const
{
	return this->size;
}

std::array<float, 3> CFigure::getColor() const
{
	return this->color;
}

void CFigure::set(const float& pivot, const float& size, const std::array<float, 3>& color)
{
	this->pivot = pivot;
	this->size = size;
	this->color = color;
}

