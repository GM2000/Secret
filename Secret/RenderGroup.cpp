
#include "Render.h"
#include <iterator>

/*���������Σ�����GLfloat*��Ҫ������������εĶ��㣬��������,��ɫ�����ݣ����з�ʽΪ ������*12������*8����ɫ*12������*12��*Count��CountΪ�����θ���*/
void renderGroup::addQuads(GLfloat* Data, int Count)
{
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 12; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 44 + VertexLoc]);
		}
		for (int TextureLoc = 0; TextureLoc < 8; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 44 + TextureLoc + 12]);
		}
		for (int ColorLoc = 0; ColorLoc < 12; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 44 + ColorLoc + 20]);
		}
		for (int NormailLoc = 0; NormailLoc < 12; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 44 + NormailLoc + 32]);
		}
		Size += 4;
	}
}
void renderGroup::addQuads(GLfloat* Data, int Count,location Loc)
{
	//��������
	for (int TriangleCount = 0; TriangleCount < Count; TriangleCount++)
	{
		for (int VertexLoc = 0; VertexLoc < 4; VertexLoc++)
		{
			VertexData.push_back(Data[TriangleCount * 44 + VertexLoc * 3 + 0] + (float)Loc.x());
			VertexData.push_back(Data[TriangleCount * 44 + VertexLoc * 3 + 1] + (float)Loc.y());
			VertexData.push_back(Data[TriangleCount * 44 + VertexLoc * 3 + 2] + (float)Loc.z());
		}
		for (int TextureLoc = 0; TextureLoc < 8; TextureLoc++)
		{
			TextureData.push_back(Data[TriangleCount * 44 + TextureLoc + 12]);
		}
		for (int ColorLoc = 0; ColorLoc < 12; ColorLoc++)
		{
			ColorData.push_back(Data[TriangleCount * 44 + ColorLoc + 20]);
		}
		for (int NormailLoc = 0; NormailLoc < 12; NormailLoc++)
		{
			NormailData.push_back(Data[TriangleCount * 44 + NormailLoc + 32]);
		}
		Size += 4;
	}
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
	std::lock_guard<std::mutex> LockGuard(Lock);

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
}