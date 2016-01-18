
#include "Secret.h"
#include "Render.h"
#include "Shader.h"

void windowsResizeCallback(GLFWwindow* Window, int Width, int Height)
{
	glm::mat4 GobalProjection = glm::perspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 5000.0f);

	glUniformMatrix4fv(NormalShader::LocProject, 1, GL_TRUE, glm::value_ptr(GobalProjection));
	
	glViewport(0, 0, Width, Height);
}
