#version 330 core

in vec3 out_Normal; 
in vec3 out_Position;
out vec4 FragColor; //--- ���� ���

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;

void main(void) 
{
	vec3 ambient = ambientStrength * lightColor;
	vec3 lightDir = normalize(lightPos - out_Position);
	vec3 pixelNorm = normalize(out_Normal);	// �ȼ��� ���������� �� �������Ͱ� �ƴ� �� ����
	vec3 diffuse = max(dot(pixelNorm, lightDir), 0.0) * lightColor;	// 90 �̻��� �� �ʿ� ����
	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4 (result, 1.0);
}
