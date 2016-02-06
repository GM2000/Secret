#pragma once

#include "Secret.h"
#include "Location.h"
#include <vector>
#include <list>
#include <mutex>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//所有渲染的VAO列表
class vbo
{
public:
	GLuint VBOBuffer[3] = {0,0,0};
	GLuint VBOSize = 0;

	vbo(GLuint *BufferID, GLuint Size);
};

class renderGroup
{
	//是否有改变
	bool HasChange = false;
public:
	//锁
	std::mutex Lock;

	//数据
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> ColorData;
	std::vector<GLfloat> NormailData;

	//Buffer
	GLuint Buffer[3];
	//大小
	GLuint Size = 0;

	//VAO的位置
	GLuint VertexArrayID = 0;
	//VAO在渲染队列中的位置
	GLuint VertexRenderArrayCount = 0;

	/*加载正方，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*12，纹理*8，颜色*16，法线*12）*Count，Count为三角形个数*/
	void addQuads(GLfloat*,int);
	/*加载正方，其中GLfloat*需要输入的是三角形的顶点，纹理，法线的数据，排列方式为 （顶点*12，纹理*8，颜色*16，法线*12）*Count，Count为三角形个数,Loc为位置*/
	void renderGroup::addQuads(GLfloat*, int, location);

	//剪切
	void cut(renderGroup*);

	//取消更改
	void unNeedRefresh();
	//更改
	void NeedRefresh();
	//有变化?
	bool hasChange();
};

//渲染组刷新列表锁
extern std::mutex RefreshRenderGroupLock;

extern std::vector<vbo> VertexArrayObject;
extern std::list<renderGroup*> RefreshRenderGroup;

//添加需要刷新的RenderGroup
void addRefreshRenderGroup(renderGroup* RenderGroup);

//刷新渲染组
void refreshRenderData();

//渲染主函数
void render();