
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>

bool saveAImg(std::vector<unsigned char>, const char* AImgName);
std::vector<unsigned char> loadAImg(const char* AImgName);
std::vector<unsigned char> loadPNG(const char* PNGName);

int main(int argc, char *argv[])
{
	std::string NewFileName = argv[1];

	NewFileName += ".AImg";

	std::cout << "[INFO]:Loading PNG" << std::endl;

	std::vector<unsigned char> PNG = loadPNG(argv[1]);

	std::cout << "[INFO]:Save to AImg" << std::endl;

	saveAImg(PNG, NewFileName.c_str());

	std::cout << "[INFO]:Load new AImg" << std::endl;

	std::vector<unsigned char> AImg = loadAImg(NewFileName.c_str());

	std::cout << "[INFO]:Checking" << std::endl;

	for (int i = 0; i < AImg.size(); i++)
	{
		if (PNG[i] != AImg[i])
		{
			std::cout << "[ERROR]:Find a wrong data" << std::endl;
		}
	}
	std::cout << "[INFO]:Complite" << std::endl;

	while (true);
}