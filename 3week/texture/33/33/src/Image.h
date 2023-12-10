#pragma once
#include "header.h"
#include "header_user.h"

class CImage
{
private:
	int m_width{};
	int m_height{};
	int m_channel_cnt{};
	uint8_t * m_data{nullptr};
public:
	CImage();
	~CImage();
public:
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_width; }
	int GetChannelCnt() const { return m_channel_cnt; }
	uint8_t* GetData() const { return m_data; }
	void SetCheckImage(int grid_x, int grid_y);
	void LoadWithStb(const std::string_view filepath);
	bool Allocate(int width, int height, int channel_cnt);
};

