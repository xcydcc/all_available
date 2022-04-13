#include <stdio.h>
#include<stdlib.h>
#define MAXE 100
#define MAXV 100
#define MAX 10
#define INF 32767  
int G[MAX][MAX];
typedef struct
{
	int vex1;
	int vex2;
	int cost;
}Edge;
void kruskal(Edge E[], int n, int e)
{
	int i, j, m1, m2, sn1, sn2, k, sum = 0;
	int vset[MAXV];
	for (i = 1; i <= n; i++)
		vset[i] = i;
	k = 1;
	j = 0;
	while (k < e)
	{
		m1 = E[j].vex1;
		m2 = E[j].vex2;
		sn1 = vset[m1];
		sn2 = vset[m2];
		if (sn1 != sn2)
		{
			printf("V%d-V%d=%d\n", m1, m2, E[j].cost);
			sum += E[j].cost;
			k++;
			if (k >= n)
				break;
			for (i = 1; i <= n; i++)
				if (vset[i] == sn2)
					vset[i] = sn1;
		}
		j++;
	}
	printf("最小权值之和=%d\n", sum);
}
int fun(Edge arr[], int low, int high)
{
	int temp;
	Edge lowx;
	lowx = arr[low];
	temp = arr[low].cost;
	while (low < high)
	{
		while (low < high && arr[high].cost >= temp)
			high--;
		if (low < high)
			arr[low++] = arr[high];
		while (low < high && arr[low].cost <= temp)
			low++;
		if (low < high)
			arr[high--] = arr[low];
	}
	arr[low] = lowx;
	return low;
}
void sort(Edge arr[], int start, int end)
{
	int pos;
	if (start < end)
	{
		pos = fun(arr, start, end);
		sort(arr, start, pos - 1);
		sort(arr, pos + 1, end);
	}
}
void prim(int G[][MAX], int n)
{
	int lowcost[MAX];
	int mstr[MAX];                     //起始节点数组
	int i, j, min, no, sum = 0;
	for (i = 2; i <= n; i++)
	{
		lowcost[i] = G[1][i];             //lowcost存放顶点1可达点的路径长度
		mstr[i] = 1;                           //初始化以1作为起始点
	}
	mstr[1] = 0;
	for (i = 2; i <= n; i++)
	{
		min = INF;
		no = 0;
		for (j = 2; j <= n; j++)
		{
			if (lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];            //找出权值最短的路径长度
				no = j;                            //找出最小的序号no 
			}
		}
		printf("V%d->V%d=%d\n", mstr[no], no, min);         //输出俩点之间的最小路径长度
		sum += min;                          //求和
		lowcost[no] = 0;                    //该处最短路径置为0 
		for (j = 2; j <= n; j++)
		{
			if (G[no][j] < lowcost[j])       //找到了更短的路径，进行路径更新
			{
				lowcost[j] = G[no][j];
				mstr[j] = no;
			}
		}
	}
	printf("最小权值之和=%d\n", sum);
}
int main()
{
	Edge E[MAXE];
	int i, j, num_e, num_n;
	printf("***********************************\n    图的最小生成树                  \n***********************************\n\n");
	printf("输入顶点数n和边数e:\n");
	scanf("%d%d", &num_n, &num_e);
	for (i = 1; i <= num_n; i++)               //prime初始化图,各项连接均为无穷
	{
		for (j = 1; j <= num_n; j++)
		{
			G[i][j] = INF;
		}
	}
	int start, end, cost;
	for (int i = 0; i < num_e; i++)
	{
		printf("输入边的信息：\n");
		scanf("%d%d%d", &start, &end, &cost);
		E[i].vex1 = start;
		E[i].vex2 = end;
		E[i].cost = cost;
		G[start][end] = cost;
		G[end][start] = cost;
	}
	sort(E, 0, num_e - 1);
	printf("\nKruskal算法来求最小生成树:\n\n");
	kruskal(E, num_n, num_e);
	printf("\nPrime算法来求最小生成树：\n\n");
	prim(G, num_n);
	getchar();
	system("pause");
	return 0;

}
