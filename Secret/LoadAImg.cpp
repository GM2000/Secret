
#include "Texture.h"
#include <iostream>

bool loadAImg(const char* AImgName,Image* Out)
{
	FILE* AImgFile;

	if (!(AImgFile = fopen(AImgName, "rb")))
	{
		std::cerr << "[Error]Could not open the file call:" << AImgName << std::endl;

		return false;
	}

	//��ȡ�ļ�ͷ
	unsigned char FileTitle[1]{};

	fread((void*)FileTitle, sizeof(FileTitle), 1, AImgFile);

	if (FileTitle[0] != 151)
	{
		std::cerr << "[ERROR]Isn't is AImg." << std::endl;

		return false;
	}

	//��ȡ�ļ���С
	fread((void*)&Out->Height, sizeof(unsigned int), 1, AImgFile);

	fread((void*)&Out->Width, sizeof(unsigned int), 1, AImgFile);


	//�ı�������С
	Out->ImageData = new unsigned char[Out->Height * Out->Width];

	//��ȡͼƬ����
	fread((void*)Out->ImageData, sizeof(unsigned char), Out->Height * Out->Width, AImgFile);

	//OK��
	fclose(AImgFile);

	return true;
}