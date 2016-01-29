
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

struct Image
{
	unsigned char* ImageData;

	unsigned int Width;
	unsigned int Height;
};
Image AImg;

Image loadAImg(const char* AImgName)
{
	FILE* AImgFile;

	if (!(AImgFile = fopen(AImgName, "rb")))
	{
		std::cout << "[Error]Could not open the file call:" << AImgName << std::endl;
	}
	//��ȡ�ļ�ͷ
	unsigned char FileTitle[1]{};

	fread((void*)FileTitle, sizeof(FileTitle), 1, AImgFile);

	if (FileTitle[0] != 151)
	{
		std::cout << "[ERROR]Isn't is AImg." << std::endl;
	}

	//��ȡ�ļ���С
	fread((void*)&AImg.Height, sizeof(unsigned int), 1, AImgFile);

	fread((void*)&AImg.Width, sizeof(unsigned int), 1, AImgFile);


	//�ı�������С
	AImg.ImageData = (unsigned char*)malloc(AImg.Height * AImg.Width * 4);

	//��ȡͼƬ����
	fread(AImg.ImageData, sizeof(unsigned char), AImg.Height * AImg.Width * 4, AImgFile);

	//OK��
	fclose(AImgFile);

	return AImg;
}