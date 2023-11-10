#pragma once

typedef struct Point
{
	float x, y;
}Point;

Point ConvertPoint(const int& x, const int& y, const int& window_width, const int& window_height)
{
	Point tmp;
	tmp.x = (double)((x - (double)window_width / 2.0) * (double)(1.0 / (double)(window_width / 2.0)));
	tmp.y = -(double)((y - (double)window_height / 2.0) * (double)(1.0 / (double)(window_height / 2.0)));

	return tmp;
}