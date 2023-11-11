#pragma once
#include "header.h"
#include "header_user.h"

class CTranslate
{
private:
	glm::mat4 model;
public:
	CTranslate();
	~CTranslate();
public:
	void set(glm::vec3 move_amount, CShader& shader);
};