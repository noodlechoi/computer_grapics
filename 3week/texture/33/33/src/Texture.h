#pragma once
#include "header.h"
#include "header_user.h"

class CTexture
{
private:
	unsigned int m_texture{};
public:
	CTexture();
	~CTexture();
public:
	const unsigned int Get() const { return m_texture; }
	void Gen();
	void Bind() const;
	void SetFilter(unsigned int min_filter, unsigned int mag_filter) const;
	void SetWrap(unsigned int swrap, unsigned int twrap) const;
	void CreateTexture();
	void SetTextureImage(CImage* image);
};

