
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

bool saveAImg(std::vector<unsigned char> ImageData, const char* AImgName)
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

	//д�������С
	size_t GetSize = ImageData.size();
	fwrite((void*)&GetSize, sizeof(size_t), 1, AImgFile);

	//д������
	fwrite((void*)&ImageData.at(0), sizeof(unsigned char), GetSize, AImgFile);

	fclose(AImgFile);
}