#include<cstdlib>
#include<stdio.h>
#include<malloc.h>
#define MAXVEX 10
typedef struct EdgeNode 
{
	int adjvex;                              // 顶点对应的下标 
	int info;		
	struct EdgeNode* next;      //指向下一个邻接点 
}EdgeNode;
typedef struct VertexNode         // 表头结点 
{
	char data;                           
	EdgeNode* firstedge;            //头指针 
}VertexNode, AdjList[MAXVEX];
typedef struct
{
	AdjList adjList;
	int numNodes, numEdges;        //顶点和边数目
}GraphAdjList;
int visited[MAXVEX] = { 0 };                           
void  CreateALGraph(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("输入顶点数和边数（以空格分隔）:\n");
	scanf("%d %d", &G->numNodes, &G->numEdges);
	for (i = 0; i < G->numNodes; i++) 
	{
		printf("请输入顶点信息:\n");
		scanf("%d", &G->adjList[i].data); 	
		G->adjList[i].firstedge = NULL; 
	}
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边上的俩个端点序号:\n");
		scanf("%d %d", &i, &j);
		e = (EdgeNode*)malloc(sizeof(EdgeNode)); 
		e->adjvex = j;					
		e->next = G->adjList[i].firstedge;	         // 将e的指针指向当前顶点上指向的结点 
		G->adjList[i].firstedge = e;		                  // 将当前顶点的指针指向e
		e = (EdgeNode*)malloc(sizeof(EdgeNode)); 
		e->adjvex = i;				                                   //无向图
		e->next = G->adjList[j].firstedge;	          
		G->adjList[j].firstedge = e;	
	}
}
void BFS(GraphAdjList* G, int v)         //广度优先遍历算法
{
	EdgeNode* p;
	int Qu[MAXVEX];
	int Front = 0, Rear = 0;
	int visit[MAXVEX];
	int w, i;
	for (i = 0; i < G->numNodes; i++)
		visit[i] = 0;
	printf("%d ", v);
	visit[v] = 1;
	Rear = (Rear + 1) % MAXVEX;
	Qu[Rear] = v;///已访问的节点进队；
	while (Front != Rear)
	{
		Front = (Front + 1) % MAXVEX;
		w = Qu[Front];
		p = G->adjList[w].firstedge;
		while (p != NULL)
		{
			if (visit[p->adjvex] == 0)                               //若当前邻接点未被访问；
			{
				printf("%d ", p->adjvex);
				visit[p->adjvex] = 1;                                  //标记已访问；
				Rear = (Rear + 1) % MAXVEX;
				Qu[Rear] = p->adjvex;
			}
			p = p->next;
		}
	}
	printf("\n");
}            
void DFS(GraphAdjList* G, int v)                       //v为初始顶点编号
{
	EdgeNode* p;
	visited[v] = 1;
	printf("%d ", v);
	p = G->adjList[v].firstedge;
	while (p != NULL)
	{
		if (visited[p->adjvex] == 0)
			DFS(G, p->adjvex);                                  //若顶点未被访问，则访问它；
		p = p->next;
	}
}
int main(void)
{
	GraphAdjList G;
	printf("******************************************\n    图的遍历输出 <广度优先和深度优先>                  \n******************************************\n\n");
	CreateALGraph(&G);
	printf("广度优先遍历递归算法的输出:\n");
	BFS(&G, 2);
	printf("深度优先遍历递归算法的输出:\n");
	DFS(&G, 2);
	system("pause");
	return 0;
}
