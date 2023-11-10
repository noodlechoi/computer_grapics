#include "pch.h"
#include "Shader.h"


Shader::Shader(const std::string& filepath, const std::string& filepath2)
	:m_FilePath_vs{ filepath }, m_FilePath_fs{ filepath2 }, m_RendererID{ 0 }
{
	string vs = ParseShader(filepath);
	string fs = ParseShader(filepath2);

	m_RendererID = CreateShader(vs, fs);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

std::string Shader::ParseShader(const std::string& filepath)
{
	std::ifstream fin(filepath);

	if (!fin.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << std::endl;
		exit(1); // ���� ���� ���� �� �� ���ڿ� ��ȯ
	}

	std::stringstream ss;
	std::string line;

	while (getline(fin, line))
	{
		ss << line << '\n'; // �� ���� ���ڿ��� �߰��ϰ� �� �ٲ� ���ڸ� ���Խ�Ŵ
	}


	return ss.str(); // ���� ������ ���ڿ��� ��ȯ
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); //���̴� ��ü ����(��������)
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // ���̴��� �ҽ� �ڵ� ����
	glCompileShader(id); // id�� �ش��ϴ� ���̴� ������

	// Error Handling(������ ���̴� ���α׷����Ҷ� ���Ӵ�...)
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); //���̴� ���α׷����κ��� ������ ���(log)�� ����
	if (result == GL_FALSE) //�����Ͽ� ������ ���
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); //log�� ���̸� ����
		char message[1024];
		glGetShaderInfoLog(id, length, &length, message); //���̸�ŭ log�� ����
		std::cout << "���̴� ������ ����! " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id); //������ ������ ��� ���̴� ����
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram(); //���̴� ���α׷� ��ü ����(int�� ����Ǵ� ���� id)
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	//�����ϵ� ���̴� �ڵ带 program�� �߰��ϰ� ��ũ
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//���̴� ���α׷��� ���������Ƿ� vs, fs ���� ���α׷��� ���̻� �ʿ� ����
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	(glUniformMatrix4fv(GetUniformLocation(name), //v�� ������ �迭�� �ǹ�
		1, //������ ����� ����
		GL_FALSE, //transpose �Ұ�����(row-major order�� �����ϴ� ��쵵 ���Ƽ�)
		&matrix[0][0])); //ù ������ �ּҰ� ����
}

unsigned int Shader::Getid()
{
	return m_RendererID;
}

int Shader::GetUniformLocation(const std::string& name)
{
	//�ݺ��ؼ� uniform�� ã�� �ʰ� map�� �����ص�
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: unform '" << name << "' doesn't exist!\n";
	}

	m_UniformLocationCache[name] = location;

	return location;
}