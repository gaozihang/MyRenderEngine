#pragma once
#include <windows.h>
#include <string>
#include <gdiplus.h>
#include <iostream>
#include "ColorRGBA.h"
#include "Math.h"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
using namespace std;

class Texture2D
{
public:
	Texture2D(wstring);
	~Texture2D();
	ColorRGBA* buffer;
	wstring Tex_path;
	int Tex_width, Tex_height;
	void LoadBitmapToColorArray();
	ColorRGBA GetPixelColor(Texture_uv);

private:
	
};

Texture2D::Texture2D(wstring input_TexPath): Tex_path(input_TexPath)
{
}

Texture2D::~Texture2D()
{
	if (buffer != NULL) delete[] buffer;
}

void Texture2D::LoadBitmapToColorArray()
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Bitmap* bmp = new Bitmap(Tex_path.c_str());
	if (!bmp)
	{
		cout << "Loading Textrue Error!";
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return;
	}
	else
	{
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();
		Tex_width = width;
		Tex_height = height;
		//Texture2D
		buffer = new ColorRGBA[width * height];
		Color color;

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				bmp->GetPixel(x, y, &color);

				buffer[y * width + x].b = (float)(color.GetBlue() / 255.0);
				buffer[y * width + x].g = (float)(color.GetGreen() / 255.0);
				buffer[y * width + x].r = (float)(color.GetRed() / 255.0);
				buffer[y * width + x].a = (float)(color.GetAlpha() / 255.0);
			}

		delete bmp;
		GdiplusShutdown(gdiplustoken);
	}
}

ColorRGBA Texture2D::GetPixelColor(Texture_uv tex)
{
	ColorRGBA color;

	int x = int(tex.u * (Tex_width - 1) + 0.5);
	int y = int(tex.v * (Tex_height - 1) + 0.5);
	if (x >= Tex_width) x = Tex_width - 1;
	if (x < 0) x = 0;
	if (y >= Tex_height) y = Tex_height - 1;
	if (y < 0) y = 0;
	//cout << "(x:y)" << x << " " << y << endl;
	color = buffer[y * Tex_width + x];
	return color;
}