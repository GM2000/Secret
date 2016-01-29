
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
	//д���ļ�ͷ
	const unsigned char AImgTitle[1] = { 151 };

	fwrite((void*)AImgTitle, sizeof(AImgTitle), 1, AImgFile);

	//д��ͼ��ߴ�
	unsigned int GetHeight = ImageData.Height;
	fwrite((void*)&GetHeight, sizeof(unsigned int), 1, AImgFile);

	unsigned int GetWidth = ImageData.Width;
	fwrite((void*)&GetWidth, sizeof(unsigned int), 1, AImgFile);

	//д������
	fwrite((void*)ImageData.ImageData, sizeof(unsigned char), GetHeight * GetWidth, AImgFile);

	fclose(AImgFile);

	return true;
}