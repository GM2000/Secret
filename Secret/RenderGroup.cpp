
#include "Render.h"
#include <iterator>

/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬��������,��ɫ�����ݣ����з�ʽΪ ������*12������*8����ɫ*16������*12��*Count��CountΪ�����θ���*/
void renderGroup::addQuads(GLfloat* Data, int Count)
{
	lock();
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 12; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 48 + VertexLoc]);
		}
		for (int TextureLoc = 0; TextureLoc < 8; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 48 + TextureLoc + 12]);
		}
		for (int ColorLoc = 0; ColorLoc < 16; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 48 + ColorLoc + 20]);
		}
		for (int NormailLoc = 0; NormailLoc < 12; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 48 + NormailLoc + 36]);
		}
		Size += 4;
	}
	unLock();
}
void renderGroup::addQuads(GLfloat* Data, int Count,location Loc)
{
	lock();
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 4; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 48 + VertexLoc * 3 + 0] + Loc.x());
			VertexData.push_back(Data[TriangleCount * 48 + VertexLoc * 3 + 1] + Loc.y());
			VertexData.push_back(Data[TriangleCount * 48 + VertexLoc * 3 + 2] + Loc.z());
		}
		for (int TextureLoc = 0; TextureLoc < 8; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 48 + TextureLoc + 12]);
		}
		for (int ColorLoc = 0; ColorLoc < 16; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 48 + ColorLoc + 20]);
		}
		for (int NormailLoc = 0; NormailLoc < 12; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 48 + NormailLoc + 36]);
		}
		Size += 4;
	}
	unLock();
}
void renderGroup::unNeedRefresh()
{
	HasChange = false;
}
void renderGroup::NeedRefresh()
{
	HasChange = true;
}
bool renderGroup::hasChange()
{
	return HasChange;
}
void renderGroup::cut(renderGroup *RenderGroup)
{
	lock();

	VertexData.clear();
	TextureData.clear();
	ColorData.clear();
	NormailData.clear();

	RenderGroup->VertexData.swap(VertexData);
	RenderGroup->TextureData.swap(TextureData);
	RenderGroup->ColorData.swap(ColorData);
	RenderGroup->NormailData.swap(NormailData);

	Size = RenderGroup->Size;
	RenderGroup->Size = 0;

	unLock();
}
void renderGroup::clear()
{
	lock();

	VertexData.clear();
	TextureData.clear();
	ColorData.clear();
	NormailData.clear();

	Size = 0;

	HasChange = false;

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