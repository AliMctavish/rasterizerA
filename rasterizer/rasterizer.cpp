// rasterizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "tgaimage.h"
#include <iostream>
#include<windows.h>    


//RANDOM COLORS FOR LINE DRAWING
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor yellow = TGAColor(0, 255, 0, 255);
const TGAColor green = TGAColor(0, 255, 255, 255);


//DDA ALGORITHIM IMPLEMENTAION
void DrawByDDA(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color)
{
	float invX = x1 - x0;
	float invY = y1 - y0;
	float Xinc = 0;
	float Yinc = 0;
	float m = invX / invY;

	if (abs(invX) < abs(invY))
	{
		int step = abs(invY);

		Xinc = invX / step;
		Yinc = invY / step;
		for (int c = 1; c < step; c++)
		{
			x0 += Xinc;
			y0 += round(Yinc);
			int rnd = round(x0);
			std::cout << x0 << std::endl;
			std::cout << y0 << std::endl;
			std::cout << rnd << std::endl;
			image.set(rnd, y0, color);
		}
	}
	if (abs(invX) >  abs(invY))
	{
		int step = abs(invX);

		Xinc = invX / step;
		Yinc = invY / step;

		for (int c = 1; c < step; c++)
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

//BRENSHAM ALGORITHIM IMPLEMENTAION
void DrawByBresnham(int x0, int y0 , int x1 , int y1 , TGAImage& image, TGAColor color)
{
	for (int x = x0; x <= x1; x += 1)
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		image.set(x, y, color);
	}
}

int main()
{
	TGAImage image(200, 200, TGAImage::RGB);
	DrawByBresnham(20, 30, 50, 80, image, red);
	DrawByBresnham(20, 30, 50, 20, image, red);
	DrawByBresnham(50, 20, 50, 80, image, green);
	image.write_tga_file("withbrensham.tga");
	system("cd E:");
	system("cd E:/Program Files/Aseprite>Aseprite.exe");

	return 0;
}
