
#include "Texture.h"
#include <iostream>

bool loadAImg(const char* AImgName, image* Out)
{
	FILE* AImgFile;

	if (!(AImgFile = fopen(AImgName, "rb")))
	{
		std::cerr << "[Error]Could not open the file call:" << AImgName << std::endl;

		return false;
	}

	//读取文件头
	unsigned char FileTitle[1]{};

	fread((void*)FileTitle, sizeof(FileTitle), 1, AImgFile);

	if (FileTitle[0] != 151)
	{
		std::cerr << "[ERROR]Isn't is AImg." << std::endl;

		return false;
	}

	//读取文件大小
	fread((void*)&Out->Height, sizeof(unsigned int), 1, AImgFile);

	fread((void*)&Out->Width, sizeof(unsigned int), 1, AImgFile);


	//改变容器大小
	Out->ImageData = (unsigned char*)malloc(Out->Height * Out->Width * 4);

	//读取图片数据
	fread(Out->ImageData, sizeof(unsigned char) * Out->Height * Out->Width * 4, 1, AImgFile);

	//OK！
	fclose(AImgFile);

	return true;
}