
#include "Render.h"

//所有渲染的VAO列表
std::vector<vao> VertexArrayObject;

//渲染线程
void refreshRenderData()
{
	//获取开始时间
	double StartTime = glfwGetTime();

	//循环直到超时
	while (glfwGetTime() - StartTime < 0.02)
	{
		//获取一个需要刷新的渲染组指针
		if (RefreshRenderGroupLock.try_lock())
		{
			//是否有要刷新的渲染组？
			if (RefreshRenderGroup.size() == 0)
			{
				RefreshRenderGroupLock.unlock();

				return;
			}

			//读取并移除
			renderGroup* GetRenderGroup = *RefreshRenderGroup.begin();
			RefreshRenderGroup.pop_front();

			//开始刷新
			std::lock_guard<std::mutex> GetRenderGroupLockGuard(GetRenderGroup->Lock);

			//是否创建了VAO
			if (GetRenderGroup->VertexArrayID == 0)
			{
				glGenVertexArrays(1, &GetRenderGroup->VertexArrayID);

				glBindVertexArray(GetRenderGroup->VertexArrayID);

				VertexArrayObject.push_back(vao(GetRenderGroup->VertexArrayID, GetRenderGroup->Size));

				//保存位置
				GetRenderGroup->VertexRenderArrayCount = VertexArrayObject.size() - 1;

				glGenBuffers(3, GetRenderGroup->Buffer);
			}
			else
			{
				glBindVertexArray(GetRenderGroup->VertexArrayID);

				glDeleteBuffers(3, GetRenderGroup->Buffer);
				//更新
				VertexArrayObject[GetRenderGroup->VertexRenderArrayCount].VAOSize = GetRenderGroup->Size;
			}

			//解锁
			RefreshRenderGroupLock.unlock();

			//是否有变化？
			if (GetRenderGroup->hasChange() && GetRenderGroup->Size > 0)
			{
				//顶点
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[0]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->VertexData.size() * sizeof(GLfloat), &GetRenderGroup->VertexData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				//颜色
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[1]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->ColorData.size() * sizeof(GLfloat), &GetRenderGroup->ColorData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, NULL);

				//纹理坐标
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[2]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->TextureData.size() * sizeof(GLfloat), &GetRenderGroup->TextureData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, NULL);

				//激活
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				GetRenderGroup->unNeedRefresh();

				//清空
				std::vector<GLfloat> Empty[4];

				GetRenderGroup->VertexData.swap(Empty[0]);
				GetRenderGroup->TextureData.swap(Empty[1]);
				GetRenderGroup->ColorData.swap(Empty[2]);
				GetRenderGroup->NormailData.swap(Empty[3]);
			}
		}
	}
}