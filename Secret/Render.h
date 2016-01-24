#pragma once

#include "Secret.h"
#include "Location.h"
#include <vector>
#include <list>
#include <mutex>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//所有渲染的VAO列表
class vao
{
public:
	GLuint VAOArray = 0;
	GLuint VAOSize = 0;

	vao(GLuint ArrayID, GLuint Size);
};

class renderGroup
{
	//锁
	std::mutex Lock;

	//是否有改变
	bool HasChange = false;
public:
	//数据
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> ColorData;
	std::vector<GLfloat> NormailData;

	GLuint Size = 0;

	//VAO的位置
	GLuint VertexArrayID = 0;

	/*加载正方，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*12，纹理*8，颜色*16，法线*12）*Count，Count为三角形个数*/
	void addQuads(GLfloat*,int);
	/*加载正方，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*12，纹理*8，颜色*16，法线*12）*Count，Count为三角形个数,Loc为位置*/
	void renderGroup::addQuads(GLfloat*, int, location);

	//清空
	void clear();

	//取消更改
	void unNeedRefresh();
	//更改
	void NeedRefresh();
	//有变化?
	bool hasChange();

	//并发
	void lock();
	void unLock();
};

//渲染组刷新列表锁
extern std::mutex RefreshRenderGroupLock;

extern std::vector<vao> VertexArrayObject;
extern std::list<renderGroup*> RefreshRenderGroup;

//添加需要刷新的RenderGroup
void addRefreshRenderGroup(renderGroup* RenderGroup);

//刷新渲染组
void refreshRenderData();

//渲染主函数
void render();