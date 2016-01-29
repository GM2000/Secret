#pragma once

#include "Secret.h"
#include <vector>

struct image
{
	unsigned char* ImageData;

	unsigned int Width;
	unsigned int Height;
};

extern std::vector<GLuint> TextureList;

bool loadAImg(const char* AImgName, image* Out);
unsigned int loadGLTexture(const char* AImgName);