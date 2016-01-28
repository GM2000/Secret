
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
	//写入文件头
	const unsigned char AImgTitle[1] = { 151 };

	fwrite((void*)AImgTitle, sizeof(AImgTitle), 1, AImgFile);

	//写入数组大小
	size_t GetSize = ImageData.size();
	fwrite((void*)&GetSize, sizeof(size_t), 1, AImgFile);

	//写入数组
	fwrite((void*)&ImageData.at(0), sizeof(unsigned char), GetSize, AImgFile);

	fclose(AImgFile);
}