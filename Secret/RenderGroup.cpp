
#include "Render.h"
#include <iterator>

/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬�������ߵ����ݣ����з�ʽΪ ������*9������*6������*9��*Count��CountΪ�����θ���*/
void renderGroup::addTriangles(GLfloat* Data, int Count)
{
	lock();
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 9; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 24 + VertexLoc]);
		}
		for (int TextureLoc = 0; TextureLoc < 6; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 24 + TextureLoc + 9]);
		}
		for (int NormailLoc = 0; NormailLoc < 9; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 24 + NormailLoc + 15]);
		}
		Size += 3;
	}
	unLock();
}
//ɾ��������(����)
void renderGroup::delTriangles(int* TrianglesLoc, int Count)
{
	lock();

	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		std::vector<GLfloat>::iterator VertexDataIt  = VertexData.begin()  + TrianglesLoc[TriangleCount] * 9;
		std::vector<GLfloat>::iterator TextureDataIt = TextureData.begin() + TrianglesLoc[TriangleCount] * 6;
		std::vector<GLfloat>::iterator NormailDataIt = NormailData.begin() + TrianglesLoc[TriangleCount] * 9;

		for (int i = 0; i < 9; i++)
		{
			VertexDataIt = VertexData.erase(VertexDataIt);
			NormailDataIt = NormailData.erase(NormailDataIt);
		}
		for (int i = 0; i < 6; i++)
		{
			TextureDataIt = TextureData.erase(TextureDataIt);
		}
		Size -= 3;
	}
	unLock();
}
void renderGroup::lock()
{
	Lock.lock();
}
void renderGroup::unLock()
{
	Lock.unlock();
}