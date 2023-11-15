#pragma once
#include "Figure.h"
#include "Type.h"

class CTriangle : public CFigure
{
protected:
	std::array<std::array<float, 3>, 3> colors;
public:
	CTriangle();
	CTriangle(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color);
	~CTriangle();
public:
	std::array<std::array<float, 3>, 3> GetPos() const;
	unsigned int GetSizeof() const;
	std::array<std::array<float, 3>, 3> GetColor() const;
	void Set(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color) override;
};
