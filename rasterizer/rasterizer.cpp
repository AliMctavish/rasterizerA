// rasterizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "tgaimage.h"
#include <iostream>


//RANDOM COLORS FOR LINE DRAWING
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor cyan = TGAColor(0, 255, 255, 255);


//DDA ALGORITHIM IMPLEMENTAION
void DrawByDDA(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	for (float t = 0.; t < 1.; t += .001) {
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(x, y, color);
	}
}

//BRENSHAM ALGORITHIM IMPLEMENTAION
void DrawByBresnham(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	int Xdeff = x1 - x0;
	int Ydeff = y1 - y0;
	if (std::abs(Xdeff) > std::abs(Ydeff))
	{
		for (int x = x0; x <= x1; x += 1)
		{
			float t = (x - x0) / (float)(x1 - x0);
			int y = y0 * (1. - t) + y1 * t;
			image.set(x, y, color);
		}
	}
	else
	{
		for (int y = y0; y <= y1; y += 1)
		{
			float t = (y - y0) / (float)(y1 - y0);
			int x = x0 * (1. - t) + x1 * t;
			image.set(x, y, color);
		}
	}
}


void DrawBySlope(int point, int slopex, int slopey, TGAImage& image, TGAColor color)
{
again:
	for (int i = 0; i <= slopex; i++)
	{
		point++;
		for (int j = 0; j <= slopey; j++)
		{
			point++;
			if (point > 100)
			{
				break;
			}
			if (i == slopex && j == slopey)
			{
				point++;
				image.set(point, point, color);

				goto again;
			}
		}
	}

}

int main()
{
	int x = 0;
	TGAImage image(200, 200, TGAImage::RGB);
	for (int i = 1; i < 100; i++)
	{
		DrawByBresnham(170 / i, 10, 30 * x, 180, image, green);
		x++;
	}
	image.write_tga_file("withbrensham.tga");
	return 0;
}
