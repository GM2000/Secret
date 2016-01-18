
#include "Render.h"
#include <iterator>

/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬��������,��ɫ�����ݣ����з�ʽΪ ������*9������*6����ɫ*12������*9��*Count��CountΪ�����θ���*/
void renderGroup::addTriangles(GLfloat* Data, int Count)
{
	lock();
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 9; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 34 + VertexLoc]);
		}
		for (int TextureLoc = 0; TextureLoc < 6; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 34 + TextureLoc + 9]);
		}
		for (int ColorLoc = 0; ColorLoc < 12; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 34 + ColorLoc + 15]);
		}
		for (int NormailLoc = 0; NormailLoc < 9; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 34 + NormailLoc + 25]);
		}
		Size += 3;
	}
	HasChange = true;

	unLock();
}
void renderGroup::addTriangles(GLfloat* Data, int Count,location Loc)
{
	lock();
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 3; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 34 + VertexLoc * 3 + 0] + Loc.x());
			VertexData.push_back(Data[TriangleCount * 34 + VertexLoc * 3 + 1] + Loc.y());
			VertexData.push_back(Data[TriangleCount * 34 + VertexLoc * 3 + 2] + Loc.z());
		}
		for (int TextureLoc = 0; TextureLoc < 6; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 34 + TextureLoc + 9]);
		}
		for (int ColorLoc = 0; ColorLoc < 12; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 34 + ColorLoc + 15]);
		}
		for (int NormailLoc = 0; NormailLoc < 9; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 34 + NormailLoc + 25]);
		}
		Size += 3;
	}
	HasChange = true;

	unLock();
}
void renderGroup::unRefresh()
{
	HasChange = false;
}
bool renderGroup::hasChange()
{
	return HasChange;
}
void renderGroup::clear()
{
	VertexData.clear();
	TextureData.clear();
	ColorData.clear();

	HasChange = false;
}

void renderGroup::lock()
{
	Lock.lock();
}
void renderGroup::unLock()
{
	Lock.unlock();
}