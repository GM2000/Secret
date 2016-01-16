#pragma once

#include "Secret.h"
#include <vector>
#include <mutex>

//所有渲染的VAO列表
class vao
{
public:
	GLuint VAOArray = 0;
	GLuint VAOSize = 0;

	vao(GLuint ArrayID, GLuint Size);
};
extern std::vector<vao> VertexArrayObject;

class renderGroup
{
	//锁
	std::mutex Lock;
public:
	//数据
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> NormailData;

	GLuint Size = 0;
	//VAO的位置
	GLuint VertexArrayID = 0;
	/*加载三角形，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*9，纹理*6，法线*9）*Count，Count为三角形个数*/
	void addTriangles(GLfloat*,int);
	//删除三角形
	void delTriangles(int*,int);

	//并发
	void lock();
	void unLock();
};

//渲染组刷新列表锁
extern std::mutex RefreshRenderGroupLock;