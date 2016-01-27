
#include "Render.h"
#include <iterator>

/*加载三角形，其中GLfloat*需要输入的是三角形的顶点，纹理，法线,颜色的数据，排列方式为 （顶点*12，纹理*8，颜色*16，法线*12）*Count，Count为三角形个数*/
void renderGroup::addQuads(GLfloat* Data, int Count)
{
	lock();
	//解析数据
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
	//解析数据
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