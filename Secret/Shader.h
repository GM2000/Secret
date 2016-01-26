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
	extern GLuint LocTranslate;
}

GLuint loadShader(shaderInfo* Shaders);