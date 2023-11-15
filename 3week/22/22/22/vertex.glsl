#version 330 core

//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1

out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����
//out vec3 out_Position;
//out vec3 normal;

uniform mat4 transform;
//uniform mat4 modelTransform;

void main(void) 
{
	gl_Position = transform * vec4 (in_Position, 1.0f);
//	normal = (transpose(inverse(modelTransform)) * vec4(
	out_Color = in_Color;
//	out_Position = 
}