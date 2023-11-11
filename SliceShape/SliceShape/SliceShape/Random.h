#pragma once
#include <random>

class CRandom
{
private:
	std::random_device rd;
	std::mt19937 gen;
public:
	CRandom();
	~CRandom();
public:
	int get(size_t start, size_t end);
	float get(float start, float end);
};

