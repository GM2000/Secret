
//以下代码来源于网络：
//http://zhidao.baidu.com/link?url=LojsGrFu0zm-yLv1gnR12sqkcsk91XfY8MqQwgpc0c0qxgFz5ImuadLmTePe7hNK0vp3DUJJf062Lx5BqAzurK
//感谢网友：@sun_siliang
#include "Chunk.h"

int partions(chunk* l[], int low, int high)
{
	chunk* prvotkey = l[low];
	l[0] = l[low];
	while (low<high)
	{
		while (low<high&& !(*l[high] < *prvotkey))
			--high;
		l[low] = l[high];
		while (low<high&& !(*l[low] > *prvotkey))
			++low;
		l[high] = l[low];
	}

	l[low] = l[0];
	return low;
}

void qsort(chunk* l[], int low, int high)
{
	int prvotloc;
	if (low<high)
	{
		prvotloc = partions(l, low, high);    //将第一次排序的结果作为枢轴
		qsort(l, low, prvotloc - 1); //递归调用排序 由low 到prvotloc-1
		qsort(l, prvotloc + 1, high); //递归调用排序 由 prvotloc+1到 high

	}
}

void quicksort(chunk* l[], int n)
{
	qsort(l, 1, n); //第一个作为枢轴 ，从第一个排到第n个
}
