
#include "Shader.h"
#include <mutex>

vao::vao(GLuint ArrayID, GLuint Size)
{
	VAOArray = ArrayID;
	VAOSize = Size;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//��Ⱦ
	RefreshRenderGroupLock.lock();

	std::vector<vao> VertexArrayObjectCopy = VertexArrayObject;

	RefreshRenderGroupLock.unlock();

	glUseProgram(NormalShader::NormalShaderID);

	for (unsigned int i = 0; i < VertexArrayObjectCopy.size(); i++)
	{
		if (VertexArrayObjectCopy[i].VAOSize > 0)
		{
			glBindVertexArray(VertexArrayObjectCopy[i].VAOArray);
			glDrawArrays(GL_QUADS, 0, VertexArrayObjectCopy[i].VAOSize);
		}
	}
}
