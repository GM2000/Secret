
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
		//是否有要刷新的渲染组？
		if (RefreshRenderGroup.size() == 0)
			return;

		//获取一个需要刷新的渲染组指针
		if (RefreshRenderGroupLock.try_lock())
		{
			renderGroup* GetRenderGroup = *RefreshRenderGroup.rbegin();
			RefreshRenderGroup.pop_front();

			RefreshRenderGroupLock.unlock();

			//开始刷新
			GetRenderGroup->lock();

			//是否有变化？
			if (GetRenderGroup->hasChange() && GetRenderGroup->Size > 0)
			{
				//有
				if (GetRenderGroup->VertexArrayID == 0)
				{
					glGenVertexArrays(1, &GetRenderGroup->VertexArrayID);
					VertexArrayObject.push_back(vao(GetRenderGroup->VertexArrayID, GetRenderGroup->Size));
				}
				glBindVertexArray(GetRenderGroup->VertexArrayID);

				glBindBuffer(GL_ARRAY_BUFFER, 1);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->VertexData.size() * sizeof(GLfloat), &GetRenderGroup->VertexData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				glBindBuffer(GL_ARRAY_BUFFER, 2);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->ColorData.size() * sizeof(GLfloat), &GetRenderGroup->ColorData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, 0, NULL);

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				GetRenderGroup->unNeedRefresh();
			}
			GetRenderGroup->unLock();
		}
	}
}