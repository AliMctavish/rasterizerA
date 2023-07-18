// rasterizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "tgaimage.h"
#include <iostream>
#include <windows.h>    


//RANDOM COLORS FOR LINE DRAWING
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor yellow = TGAColor(0, 255, 0, 255);
const TGAColor green = TGAColor(0, 255, 255, 255);


//DDA ALGORITHIM IMPLEMENTAION
void DrawByDDA(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color)
{
	for (float t = 0.; t < 1.; t += .01) {
		int x = x0 * t;
		int y = y0 * t;
		image.set(x, y, color);
	}
}

//BRENSHAM ALGORITHIM IMPLEMENTAION
void DrawByBresnham(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	for (int x = x0; x <= x1; x += 1)
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		image.set(x, y, color);
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
	TGAImage image(200, 200, TGAImage::RGB);
	DrawBySlope(30,2,.1, image, red);
	DrawByDDA(30,60,70,80, image, red);
	DrawByDDA(70,80,100,120, image, red);
	DrawByDDA(100,120,30,60, image, red);
	image.write_tga_file("withbrensham.tga");
	return 0;
}
