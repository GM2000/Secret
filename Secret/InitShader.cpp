
#include "Secret.h"
#include "Shader.h"

void windowsResizeCallback(GLFWwindow*, int, int);

const char* readShader(const char* FileName);

void initShader()
{
	shaderInfo NormalShaderInfo[] = {
		{ GL_VERTEX_SHADER, "res\\GLSL\\Normail3D.vert" },
		{ GL_FRAGMENT_SHADER, "res\\GLSL\\Normail3D.frag" },
		{ GL_NONE, NULL } };

	NormalShader::NormalShaderID = loadShader(NormalShaderInfo);
	NormalShader::LocProject = glGetUniformLocation(NormalShader::NormalShaderID, "uni_projection");
	NormalShader::LocRotate = glGetUniformLocation(NormalShader::NormalShaderID, "uni_rotate");
	NormalShader::LocTranslate = glGetUniformLocation(NormalShader::NormalShaderID, "uni_translate");

	//…Ë÷√ ”ø⁄
	int WindowWidth;
	int WindowHeight;

	glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);
	windowsResizeCallback(Window, WindowWidth, WindowHeight);
}