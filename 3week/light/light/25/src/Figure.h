#pragma once
#include "header.h"
#include <array>

// ��� �������� �߻� Ŭ����
class CFigure
{
protected:
	// ����, ���� ���� ������, ����(�Ѱ��� ����)
	std::pair<float, float> m_pivot;
	float m_size;
	std::array<float, 3> m_color;
public:
	CFigure();
	CFigure(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color);
	virtual ~CFigure();
public:
	virtual std::pair<float, float> GetPivot() const;
	float GetSize() const;
	std::array<float, 3> GetColor() const;
	virtual void Set(const std::pair<float, float>& m_pivot, const float& m_size, const std::array<float, 3>& m_color);
};

