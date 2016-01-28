
#define _CRT_SECURE_NO_WARNINGS

#include "LIBPNG\png.h"
#include <iostream>
#include <vector>

std::vector<unsigned char> loadPNG(const char* PNGName)
{
	FILE* PNGFile;

	if (!(PNGFile = fopen(PNGName, "rb")))
	{
		std::cout << "[Error]Could not find the texture call:" << PNGName << std::endl;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

	if (!png_ptr)
	{
		fclose(PNGFile);
		std::cout << "[Error]Could not read the PNG" << std::endl;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);

	if (!info_ptr)
	{
		fclose(PNGFile);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		std::cout << "[Error]Could not get the info of the PNG" << std::endl;
	}

	setjmp(png_jmpbuf(png_ptr));

	png_init_io(png_ptr, PNGFile);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

	int pic_width = png_get_image_width(png_ptr, info_ptr);
	int pic_height = png_get_image_height(png_ptr, info_ptr);

	int color_type = png_get_color_type(png_ptr, info_ptr);
	int channels = png_get_channels(png_ptr, info_ptr);

	if (channels != 4)
	{
		std::cout << "[Error]Could not find the alpha channel" << std::endl;
	}
	std::vector<unsigned char> PNGData;

	PNGData.resize(sizeof(unsigned char)*pic_height * pic_width * channels);

	png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < pic_height; i++)
	{
		for (int j = 0; j < pic_width; j++)
		{
			for (int k = 0; k < channels; k++)
			{
				PNGData[i*pic_width*channels + j*channels + k] = row_pointers[i][j*channels + k];
			}
		}
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(PNGFile);

	return PNGData;
}