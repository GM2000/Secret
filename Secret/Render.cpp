
#include "Shader.h"
#include <mutex>

vbo::vbo(GLuint *BufferID, GLuint Size)
{
	for (int i = 0; i < 3; i++)
	{
		VBOBuffer[i] = BufferID[i];
	}
	VBOSize = Size;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//渲染
	RefreshRenderGroupLock.lock();

	std::vector<vbo> VertexArrayObjectCopy = VertexArrayObject;

	RefreshRenderGroupLock.unlock();

	glUseProgram(NormalShader::NormalShaderID);

	glBindVertexArray(1);

	for (unsigned int i = 0; i < VertexArrayObjectCopy.size(); i++)
	{
		//顶点
		glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObjectCopy[i].VBOBuffer[0]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//颜色
		glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObjectCopy[i].VBOBuffer[1]);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, NULL);

		//纹理坐标
		glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObjectCopy[i].VBOBuffer[2]);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, NULL);

		//激活
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(GL_QUADS, 0, VertexArrayObjectCopy[i].VBOSize);
	}
}
