#pragma once
#include "header.h"
#include <array>

// 모든 도형들의 추상 클래스
class CFigure
{
protected:
	// 중점, 가로 세로 사이즈, 색깔(한가지 색상만)
	std::pair<float, float> pivot;
	float size;
	std::array<float, 3> color;
public:
	CFigure();
	CFigure(const std::pair<float, float>& pivot, const float& size, const std::array<float, 3>& color);
	virtual ~CFigure();
public:
	virtual std::pair<float, float> getPivot() const;
	float getSize() const;
	std::array<float, 3> getColor() const;
	virtual void set(const std::pair<float, float>& pivot, const float& size, const std::array<float, 3>& color);
};

