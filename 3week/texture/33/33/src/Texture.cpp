#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	if (m_texture) {
		glDeleteTextures(1, &m_texture);
	}
}

void CTexture::Gen()
{
	glGenTextures(1, &m_texture);
}

void CTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void CTexture::SetFilter() const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void CTexture::SetWrap() const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CTexture::CreateTexture()
{
	Gen();
	Bind();
	SetFilter();
	SetWrap();
}

void CTexture::SetTextureImage(std::string_view name)
{
	int width, height, nrChannels;
	unsigned char* data;

	Bind();
	data = stbi_load(name.data(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}