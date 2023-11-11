#include "Tanslate.h"

CTranslate::CTranslate() : model{ glm::mat4(1.0f) }
{
}

CTranslate::~CTranslate()
{
}

void CTranslate::set(glm::vec3 move_amount,  CShader& shader)
{

	model = glm::translate(model, move_amount);
	unsigned int modelLocation = shader.getUniform("transform");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}
