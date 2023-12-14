#pragma once
#include "header.h"

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
	void SetFilter() const;
	void SetWrap() const;
	void CreateTexture();
	void SetTextureImage(std::string_view name);
};

