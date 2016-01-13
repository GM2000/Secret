#pragma once

#include "Secret.h"
#include <vector>
#include <mutex>

class renderGroup
{
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> NormailData;
public:
	//锁
	std::mutex Lock;
	/*加载三角形，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*9，纹理*6，法线*9）*Count，Count为三角形个数*/
	void addTriangles(GLfloat*,int);
	//删除三角形
	void delTriangles(int*,int);
};