#include "Texture.h"

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

void CTexture::SetFilter(unsigned int min_filter, unsigned int mag_filter) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

void CTexture::SetWrap(unsigned int swrap, unsigned int twrap) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, swrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, twrap);
}

void CTexture::CreateTexture()
{
	glGenTextures(1, &m_texture);
	Bind();
	SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void CTexture::SetTextureImage(CImage* image)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
	glGenerateMipmap(GL_TEXTURE_2D);
}
