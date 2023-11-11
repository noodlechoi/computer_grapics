#pragma once
#include "header.h"
#include <array>

// ��� �������� �߻� Ŭ����
class CFigure
{
protected:
	// ����, ���� ���� ������, ����(�Ѱ��� ����)
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

