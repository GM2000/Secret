
#include "Secret.h"
#include "Shader.h"
#include <iostream>

typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shaderInfo;

const char* readShader(const char* FileName);

//����һ������shader
GLuint loadShader(shaderInfo* Shaders)
{
	//����Ƿ�Ϊ��
	if (Shaders == NULL)
	{
		std::cerr << "[WARNING]Shader is empty!" << std::endl;
		return 0;
	}

	//������ɫ������
	GLuint Program = glCreateProgram();

	shaderInfo* Entry = Shaders;

	//ѭ��������ɫ��
	while (Entry->Type != GL_NONE)
	{
		//����Shader
		GLuint Shader = glCreateShader(Entry->Type);

		//��ȡShader����
		const GLchar* Source = readShader(Entry->FileName);

		//�������Ƿ�Ϊ��
		if (Source == NULL)
		{
			//ɾ��Shader
			for (Entry = Shaders; Entry->Type != GL_NONE; ++Entry)
			{
				glDeleteShader(Shader);
			}
			return 0;
		}

		//��Դ��
		glShaderSource(Shader, 1, &Source, NULL);
		delete[] Source;

		//����Դ��
		glCompileShader(Shader);

		//��ȡ����״̬
		GLint compiled;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &compiled);

		//����������
		if (!compiled)
		{
			//��ȡ�������
			GLsizei len;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(Shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;

			return 0;
		}

		//��Shader����ɫ������
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
	return Program;
}

//��ȡShader����
const char* readShader(const char* FileName)
{
	//��ȡ�ļ�
	FILE* infile = fopen(FileName, "rb");

	//�Ƿ��ȡ
	if (!infile)
	{
		std::cerr << "[ERROR]Unable to open file '" << FileName << "'" << std::endl;

		return NULL;
	}

	//���ö�ȡλ��
	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//��ȡ����
	GLchar* source = new GLchar[len + 1];

	//��ȡ���ر�
	fread(source, 1, len, infile);
	fclose(infile);

	//�����
	source[len] = 0;

	//����
	return const_cast<const GLchar*>(source);
}

void initShader()
{
	shaderInfo NormalShader[] = {
		{ GL_VERTEX_SHADER, "res\\GLSL\\Normail3D.vert" },
		{ GL_FRAGMENT_SHADER, "res\\GLSL\\Normail3D.frag" },
		{ GL_NONE, NULL } };

	NormalShader::NormalShaderID = loadShader(NormalShader);
}