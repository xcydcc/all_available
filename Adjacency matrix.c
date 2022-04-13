#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define INF 32767
/*---------------------------------------------------------------*/
typedef struct node
{
	int dest;                     //目标节点位置
	int cost;                     //边的权值
	struct node* next;      //下一边链接指针
}EdgeNode;
typedef struct
{
	int data;                    //顶点数据
	EdgeNode* adj;        //边链表头指针
}Dingdian;
typedef struct
{
	Dingdian List[MAX];                //邻接表
	int n, e;
}Graph;
typedef struct
{
	int edges[MAX][MAX];              // 边数组
	int n, e;
	int DATA[MAX];                           //存放顶点信息
}MGraph;
/*---------------------------------------------------------------*/
void start(MGraph* G)
{
	int i, j;
	for (i = 0; i < G->n; i++)
		for (j = 0; j < G->n; j++)
		{
			if (i == j)
			{
				G->edges[i][j] = 0;           //使邻接矩阵对角线全部置0,进行初始化
			}
			else
			{
				G->edges[i][j] = INF;
			}
		}
}
/*---------------------------------------------------------------*/
void creat(MGraph* G, Graph& A)
{
	printf("输入该图的顶点数n和边数e:\n");
	int temp, a, b, c, d, s;
	scanf("%d%d", &c, &d);
	G->n = c;
	G->e = d;
	A.n = c;
	A.e = d;
	start(G);
	for (temp = 0; temp < G->n; temp++)
	{
		printf("请输入顶点的信息（如序号等）\n");
		scanf("%d", &G->DATA[temp]);
		A.List[temp].data = G->DATA[temp];
		A.List[temp].adj = NULL;
	}
	for (temp = 0; temp < G->e; temp++)
	{
		printf("输入边的相关信息:\n");
		scanf("%d%d%d", &a, &b, &s);
		G->edges[a - 1][b - 1] = s;
		EdgeNode* p = new EdgeNode;
		p->dest = b - 1; p->cost = s;
		p->next = A.List[a - 1].adj;
		A.List[a - 1].adj = p;
	}
}
/*---------------------------------------------------------------*/
void show01(MGraph* G)
{
	int i, j, k;
	for (i = 0; i < G->n; i++)
	{
		printf("\n\n");
		for (j = 0; j < G->n; j++)
		{
			printf("%-8d", G->edges[i][j]);
		}
	}
	printf("\n\n边集合为:\n");
	for (i = 0; i < G->n; i++)
		for (j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] != 0 && G->edges[i][j] != INF)
				printf("<%d,%d>  ", i + 1, j + 1);
		}
}
/*---------------------------------------------------------------*/
void show02(Graph G)//输出邻接表
{
	for (int i = 0; i < G.n; i++)
	{
		printf("%d", G.List[i].data);
		EdgeNode* p = G.List[i].adj;
		while (p != NULL)
		{
			printf(" -> (");
			printf("%d", p->dest + 1);
			printf(",%d）", p->cost);
			p = p->next;
		}
		printf("\n");
	}
}
/*---------------------------------------------------------------*/
int main()
{
	MGraph hhy;
	Graph HHY;
	printf("***********************************\n    邻接矩阵和邻接表的储存                  \n***********************************\n\n");
	creat(&hhy, HHY);
	printf("\n\n邻接矩阵为：");
	show01(&hhy);
	printf("\n\n邻接表为：\n");
	show02(HHY);
	getchar();
	system("pause");
	return 0;
}
