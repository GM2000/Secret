
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>

struct Image
{
	unsigned char* ImageData;

	unsigned int Width;
	unsigned int Height;
};
bool saveAImg(Image, const char* AImgName);
Image loadAImg(const char* AImgName);
Image loadPNG(const char* PNGName);

int main(int argc, char *argv[])
{
	std::string NewFileName = argv[1];

	NewFileName += ".AImg";

	std::cout << "[INFO]:Loading PNG" << std::endl;

	Image PNG = loadPNG(argv[1]);

	std::cout << "[INFO]:Save to AImg" << std::endl;

	saveAImg(PNG, NewFileName.c_str());

	std::cout << "[INFO]:Load new AImg" << std::endl;

	Image AImg = loadAImg(NewFileName.c_str());

	std::cout << "[INFO]:Checking" << std::endl;

	for (int i = 0; i < AImg.Height * AImg.Width * 4; i++)
	{
		if (PNG.ImageData[i] != AImg.ImageData[i])
		{
			std::cout << "[ERROR]:Find a wrong data" << std::endl;
		}
	}
	std::cout << "[INFO]:Complite" << std::endl;

	while (true);
}