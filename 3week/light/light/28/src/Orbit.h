#pragma once
#include "header.h"
#include "header_user.h"

class COrbit
{
private:
	CVAO* m_vao{};
	CBuffer* m_vertexbuffer{};
public:
	COrbit();
	~COrbit();
public:
	void Init(const std::vector<Vertex>& vertices);
	void Draw(const CShader* program) const;
	void update();
};

