
#include "Render.h"
#include <iterator>

/*加载三角形，其中GLfloat*需要输入的是三角形的顶点，纹理，法线,颜色的数据，排列方式为 （顶点*9，纹理*6，颜色*12，法线*9）*Count，Count为三角形个数*/
void renderGroup::addTriangles(GLfloat* Data, int Count)
{
	lock();
	//解析数据
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
	//解析数据
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