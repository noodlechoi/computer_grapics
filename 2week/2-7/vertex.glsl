#version 330 core

// In_Position : index 0
// In_Color : 1

layout (location = 0) in vec3 In_Position;
layout (location = 1) in vec3 In_Color;
out vec3 out_Color;

void main()
{
	gl_Position = vec4(In_Position.x, In_Position.y, In_Position.z, 1.0);
	out_Color = In_Color;
}