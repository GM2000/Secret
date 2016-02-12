
//���´�����Դ�����磺
//http://zhidao.baidu.com/link?url=LojsGrFu0zm-yLv1gnR12sqkcsk91XfY8MqQwgpc0c0qxgFz5ImuadLmTePe7hNK0vp3DUJJf062Lx5BqAzurK
//��л���ѣ�@sun_siliang
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
		prvotloc = partions(l, low, high);    //����һ������Ľ����Ϊ����
		qsort(l, low, prvotloc - 1); //�ݹ�������� ��low ��prvotloc-1
		qsort(l, prvotloc + 1, high); //�ݹ�������� �� prvotloc+1�� high

	}
}

void quicksort(chunk* l[], int n)
{
	qsort(l, 1, n); //��һ����Ϊ���� ���ӵ�һ���ŵ���n��
}
