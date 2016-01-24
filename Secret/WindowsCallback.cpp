
#include "Secret.h"
#include "Render.h"
#include "Shader.h"

void windowsResizeCallback(GLFWwindow* Window, int Width, int Height)
{
	glUniformMatrix4fv(NormalShader::LocProject, 1, GL_TRUE, glm::value_ptr(glm::perspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 5000.0f)));
	
	glViewport(0, 0, Width, Height);
}
