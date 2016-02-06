#pragma once

#include "Secret.h"
#include "Location.h"
#include <vector>
#include <list>
#include <mutex>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//������Ⱦ��VAO�б�
class vbo
{
public:
	GLuint VBOBuffer[3] = {0,0,0};
	GLuint VBOSize = 0;

	vbo(GLuint *BufferID, GLuint Size);
};

class renderGroup
{
	//�Ƿ��иı�
	bool HasChange = false;
public:
	//��
	std::mutex Lock;

	//����
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> ColorData;
	std::vector<GLfloat> NormailData;

	//Buffer
	GLuint Buffer[3];
	//��С
	GLuint Size = 0;

	//VAO��λ��
	GLuint VertexArrayID = 0;
	//VAO����Ⱦ�����е�λ��
	GLuint VertexRenderArrayCount = 0;

	/*��������������GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*12������*8����ɫ*16������*12��*Count��CountΪ�����θ���*/
	void addQuads(GLfloat*,int);
	/*��������������GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*12������*8����ɫ*16������*12��*Count��CountΪ�����θ���,LocΪλ��*/
	void renderGroup::addQuads(GLfloat*, int, location);

	//����
	void cut(renderGroup*);

	//ȡ������
	void unNeedRefresh();
	//����
	void NeedRefresh();
	//�б仯?
	bool hasChange();
};

//��Ⱦ��ˢ���б���
extern std::mutex RefreshRenderGroupLock;

extern std::vector<vbo> VertexArrayObject;
extern std::list<renderGroup*> RefreshRenderGroup;

//�����Ҫˢ�µ�RenderGroup
void addRefreshRenderGroup(renderGroup* RenderGroup);

//ˢ����Ⱦ��
void refreshRenderData();

//��Ⱦ������
void render();