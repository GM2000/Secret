#pragma once

#include "Secret.h"
#include "Location.h"
#include <vector>
#include <list>
#include <mutex>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//������Ⱦ��VAO�б�
class vao
{
public:
	GLuint VAOArray = 0;
	GLuint VAOSize = 0;

	vao(GLuint ArrayID, GLuint Size);
};

class renderGroup
{
	//��
	std::mutex Lock;

	//�Ƿ��иı�
	bool HasChange = false;
public:
	//����
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> ColorData;
	std::vector<GLfloat> NormailData;

	GLuint Size = 0;

	//VAO��λ��
	GLuint VertexArrayID = 0;

	/*��������������GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*12������*8����ɫ*16������*12��*Count��CountΪ�����θ���*/
	void addQuads(GLfloat*,int);
	/*��������������GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*12������*8����ɫ*16������*12��*Count��CountΪ�����θ���,LocΪλ��*/
	void renderGroup::addQuads(GLfloat*, int, location);

	//���
	void clear();

	//ȡ������
	void unNeedRefresh();
	//����
	void NeedRefresh();
	//�б仯?
	bool hasChange();

	//����
	void lock();
	void unLock();
};

//��Ⱦ��ˢ���б���
extern std::mutex RefreshRenderGroupLock;

extern std::vector<vao> VertexArrayObject;
extern std::list<renderGroup*> RefreshRenderGroup;

//�����Ҫˢ�µ�RenderGroup
void addRefreshRenderGroup(renderGroup* RenderGroup);

//ˢ����Ⱦ��
void refreshRenderData();

//��Ⱦ������
void render();