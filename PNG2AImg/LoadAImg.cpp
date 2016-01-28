
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

std::vector<unsigned char> loadAImg(const char* AImgName)
{
	std::vector<unsigned char> ImageData;

	FILE* AImgFile;

	if (!(AImgFile = fopen(AImgName, "rb")))
	{
		std::cout << "[Error]Could not open the file call:" << AImgName << std::endl;
	}
	//��ȡ�ļ�ͷ
	unsigned char FileTitle[1]{};

	fread((void*)FileTitle, sizeof(FileTitle), 1, AImgFile);

	if (FileTitle[0] != 151);
	{
		std::cout << "[ERROR]Isn't is AImg." << std::endl;
	}
	//��ȡ�ļ���С
	size_t Size;

	fread((void*)&Size, sizeof(size_t), 1, AImgFile);

	//�ı�������С
	ImageData.resize(Size);

	//��ȡͼƬ����
	fread((void*)&ImageData.at(0), sizeof(unsigned char), Size, AImgFile);

	//OK��
	fclose(AImgFile);

	return ImageData;
}