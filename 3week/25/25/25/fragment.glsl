#version 330 core

in vec3 out_Normal; 
in vec3 out_Position;
out vec4 FragColor; //--- ���� ���

uniform vec3 viewPos;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Meterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Meterial meterial;

void main(void) 
{
	vec3 ambient = meterial.ambient * light.ambient;

	vec3 lightDir = normalize(light.position - out_Position);
	vec3 pixelNorm = normalize(out_Normal);	// �ȼ��� ���������� �� �������Ͱ� �ƴ� �� ����
	float diff = max(dot(pixelNorm, lightDir), 0.0);	// 90 �̻��� �� �ʿ� ����
	vec3 diffuse = diff * meterial.diffuse * light.diffuse;

	vec3 viewDir = normalize(viewPos - out_Position);
	vec3 reflectDir = reflect(-lightDir, pixelNorm); // �Ի簢�� ����
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), meterial.shininess); // specularShininess ���� Ŭ ���� ���̶���Ʈ�� ������ ������
	vec3 specular = spec * meterial.specular * light.specular;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4 (result, 1.0);
}
