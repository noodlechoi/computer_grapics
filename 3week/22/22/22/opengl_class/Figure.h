#pragma once
#include "header.h"
#include <array>

// 모든 도형들의 추상 클래스
class CFigure
{
protected:
	// 중점, 가로 세로 사이즈, 색깔(한가지 색상만)
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

