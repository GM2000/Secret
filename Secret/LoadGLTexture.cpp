
#include "Texture.h"
#include "Secret.h"

unsigned int loadGLTexture(const char* AImgName)
{
	image Image;
	
	if (!loadAImg(AImgName, &Image))
		return 0;

	GLuint TextureID = 0;

	glGenTextures(1, &TextureID);

	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.Width, Image.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.ImageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	free(Image.ImageData);

	return true;
}