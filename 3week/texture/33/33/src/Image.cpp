#include "Image.h"

CImage::CImage()
{
}

CImage::~CImage()
{
	if (m_data) {
		stbi_image_free(m_data);
	}
}

void CImage::SetCheckImage(int grid_x, int grid_y)
{
	for (int j = 0; j < m_height; ++j) {
		for (int i = 0; i < m_width; ++i) {
			int pos = (j * m_width + i) * m_channel_cnt;
			bool even = ((i / grid_x) + (j / grid_y)) % 2 == 0;
			unsigned int value = even ? 255 : 0;
			for (int k = 0; k < m_channel_cnt; ++k) {
				m_data[pos + k] = value;
				if (m_channel_cnt > 3) m_data[3] = 255;
			}
		}
	}
}

void CImage::LoadWithStb(const std::string_view filepath)
{
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(filepath.data(), &m_width, &m_height, &m_channel_cnt, 0);
}

bool CImage::Allocate(int width, int height, int channel_cnt)
{
	m_width = width;
	m_height = height;
	m_channel_cnt = channel_cnt;
	m_data = (uint8_t*)malloc(m_width * m_height * m_channel_cnt);
	return m_data ? true : false;
}
