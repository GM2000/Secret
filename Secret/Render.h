#pragma once

#include "Secret.h"
#include <vector>
#include <mutex>

//������Ⱦ��VAO�б�
class vao
{
public:
	GLuint VAOArray = 0;
	GLuint VAOSize = 0;

	vao(GLuint ArrayID, GLuint Size);
};
extern std::vector<vao> VertexArrayObject;

class renderGroup
{
	//��
	std::mutex Lock;
public:
	//����
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> NormailData;

	GLuint Size = 0;
	//VAO��λ��
	GLuint VertexArrayID = 0;
	/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*9������*6������*9��*Count��CountΪ�����θ���*/
	void addTriangles(GLfloat*,int);
	//ɾ��������
	void delTriangles(int*,int);

	//����
	void lock();
	void unLock();
};

//��Ⱦ��ˢ���б���
extern std::mutex RefreshRenderGroupLock;