
#include "Shader.h"

//读取Shader程序
const char* readShader(const char* FileName)
{
	//读取文件
	FILE* infile = fopen(FileName, "rb");

	//是否读取
	if (!infile)
	{
		std::cerr << "[ERROR]Unable to open file '" << FileName << "'" << std::endl;

		return NULL;
	}

	//设置读取位置
	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//读取数据
	GLchar* source = new GLchar[len + 1];

	//读取并关闭
	fread(source, 1, len, infile);
	fclose(infile);

	//最后处理
	source[len] = 0;

	//返回
	return const_cast<const GLchar*>(source);
}

//加载一个shader
GLuint loadShader(shaderInfo* Shaders)
{
	//检测是否为空
	if (Shaders == NULL)
	{
		std::cerr << "[WARNING]Shader is empty!" << std::endl;
		return 0;
	}

	//创建着色器程序
	GLuint Program = glCreateProgram();

	shaderInfo* Entry = Shaders;

	//循环编译着色器
	while (Entry->Type != GL_NONE)
	{
		//创建Shader
		GLuint Shader = glCreateShader(Entry->Type);

		//读取Shader代码
		const GLchar* Source = readShader(Entry->FileName);

		//检测代码是否为空
		if (Source == NULL)
		{
			//删除Shader
			for (Entry = Shaders; Entry->Type != GL_NONE; ++Entry)
			{
				glDeleteShader(Shader);
			}
			return 0;
		}

		//绑定源码
		glShaderSource(Shader, 1, &Source, NULL);
		delete[] Source;

		//编译源码
		glCompileShader(Shader);

		//获取编译状态
		GLint compiled;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &compiled);

		//如果编译出错
		if (!compiled)
		{
			//获取错误并输出
			GLsizei len;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(Shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;

			return 0;
		}

		//绑定Shader到着色器程序
		glAttachShader(Program, Shader);

		++Entry;
	}
	glLinkProgram(Program);

	GLint linked;
	glGetProgramiv(Program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(Program, len, &len, log);
		std::cerr << "[ERROR]Shader linking failed: " << log << std::endl;
		delete[] log;
		return 0;
	}
	glUseProgram(Program);

	return Program;
}
