#pragma once

struct Image
{
	unsigned char* ImageData;

	unsigned int Width;
	unsigned int Height;
};

bool loadAImg(const char* AImgName, Image* Out);