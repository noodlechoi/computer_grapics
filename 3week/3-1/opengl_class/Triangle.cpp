#include "Triangle.h"
#include "Type.h"

CTriangle::CTriangle() : CFigure()
{
}

CTriangle::CTriangle(const float& pivot, const float& size, const std::array<float, 3>& color) : CFigure(pivot, size, color)
{
	// �� �������� ������ ���� �ֱ�
	for (int i = 0; i < 3; ++i) {
		this->colors[i] = { color[0],  color[1], color[2] };
	}
}

CTriangle::~CTriangle()
{
}

std::array<std::array<float, 3>, 3> CTriangle::getPos() const
{
	// pivot���� ���� ����
	// ���� : size / 2
	// ���� : (����) / tan30
	
	float width = size / 2;
	float height = width / tan(toRadian(30));


	// �ݽð� �������� ��ȯ
	// ����, ������ ��
	return { pivot - width, pivot - height, 1.0f, {pivot + width, pivot - height, 1.0f}, {pivot, pivot + height, 1.0f} };
}

unsigned int CTriangle::getSizeOf() const
{
	return sizeof(float) * 9;
}

std::array<std::array<float, 3>, 3> CTriangle::getColor() const
{
	return this->colors;
}

void CTriangle::set(const float& pivot, const float& size, const std::array<float, 3>& color)
{
	CFigure::set(pivot, size, color);

	for (int i = 0; i < 3; ++i) {
		this->colors[i] = { color[0],  color[1], color[2] };
	}
}
