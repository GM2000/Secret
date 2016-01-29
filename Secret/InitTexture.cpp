
#include "Texture.h"

std::vector<GLuint> TextureList;

bool initTextures()
{
	int LoadTexture = loadGLTexture("res\\Texture\\BlockTexture.AImg");

	return true;
}