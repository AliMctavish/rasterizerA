// rasterizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "tgaimage.h"
#include <iostream>


const TGAColor red = TGAColor(255, 0, 0, 255);

void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color)
{
	float invX = x1 - x0;
	float invY = y1 - y0;
	float Xinc = 0;
	float Yinc = 0;
	float m = invX / invY;

	if (abs(invX) < abs(invY))
	{
		Xinc = invX / invY;
		Yinc = invY / invY;

		for (int c = invY; c > y1; c++)
		{
			y0 += Yinc;
			x0 += Yinc;
			image.set(round(x0), y0, color);
		}
	}
	if (abs(invX) >  abs(invY))
	{
		int step = abs(invX);

		Xinc = invX / step;
		Yinc = invY / step;

		for (int c = 1; c <= invX; c++)
		{
			x0 += round(Xinc);
			y0 += Yinc;
			int rnd = round(y0);
			std::cout << x0 << std::endl;
			std::cout << y0 << std::endl;
			std::cout << rnd << std::endl;
			image.set(x0, rnd, color);
		}
	}
}

int main()
{
	TGAImage image(200, 200, TGAImage::RGB);
	line(13, 20, 80, 40, image, red);
	image.write_tga_file("wrcce.tga");
	return 0;
}
