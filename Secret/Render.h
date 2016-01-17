#pragma once

#include "Secret.h"
#include "Location.h"
#include <vector>
#include <list>
#include <mutex>

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
public:
	//����
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> ColorData;
	std::vector<GLfloat> NormailData;

	GLuint Size = 0;

	//�Ƿ��иı�
	bool HasChange = false;

	//VAO��λ��
	GLuint VertexArrayID = 0;

	/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*9������*6����ɫ*12������*9��*Count��CountΪ�����θ���*/
	void addTriangles(GLfloat*,int);
	/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*9������*6����ɫ*12������*9��*Count��CountΪ�����θ���,LocΪλ��*/
	void renderGroup::addTriangles(GLfloat*, int, location);

	//���
	void clear();

	//����
	void lock();
	void unLock();
};

//��Ⱦ��ˢ���б���
extern std::mutex RefreshRenderGroupLock;

extern std::vector<vao> VertexArrayObject;
extern std::list<renderGroup*> RefreshRenderGroup;