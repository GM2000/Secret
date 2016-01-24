#pragma once

#include "Render.h"

typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shaderInfo;

namespace NormalShader
{
	extern GLuint NormalShaderID;

	extern GLuint LocProject;
	extern GLuint LocRotate;
}

GLuint loadShader(shaderInfo* Shaders);