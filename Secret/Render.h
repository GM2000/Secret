#pragma once

#include "Secret.h"
#include <vector>
#include <mutex>

class renderGroup
{
	std::vector<GLfloat> VertexData;
	std::vector<GLfloat> TextureData;
	std::vector<GLfloat> NormailData;
public:
	//��
	std::mutex Lock;
	/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*9������*6������*9��*Count��CountΪ�����θ���*/
	void addTriangles(GLfloat*,int);
	//ɾ��������
	void delTriangles(int*,int);
};