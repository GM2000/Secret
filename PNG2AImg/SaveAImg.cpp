
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

struct Image
{
	unsigned char* ImageData;

	unsigned int Width;
	unsigned int Height;
};

bool saveAImg(Image ImageData, const char* AImgName)
{
	FILE* AImgFile;

	if (!(AImgFile = fopen(AImgName, "wb")))
	{
		std::cout << "[Error]Could not open the file call:" << AImgName << std::endl;
		return false;
	}
	//写入文件头
	const unsigned char AImgTitle[1] = { 151 };

	fwrite((void*)AImgTitle, sizeof(AImgTitle), 1, AImgFile);

	//写入图像尺寸
	unsigned int GetHeight = ImageData.Height;
	fwrite((void*)&GetHeight, sizeof(unsigned int), 1, AImgFile);

	unsigned int GetWidth = ImageData.Width;
	fwrite((void*)&GetWidth, sizeof(unsigned int), 1, AImgFile);

	//写入数组
	fwrite((void*)ImageData.ImageData, sizeof(unsigned char), GetHeight * GetWidth, AImgFile);

	fclose(AImgFile);

	return true;
}