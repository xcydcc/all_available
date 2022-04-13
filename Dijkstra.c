/*
--------------------------------------------------------------------------------------------
                                                                                                                                     +
                                                                                         +
       1、编程随机选取图中的任一顶点作为源点。                                                            +
       2、基于Dijkstra算法求取源点到图中其他所有顶点的最短路径及最短路径长度。       +
       3、使用堆栈方法输出从源点到每个终点的最短路径及最短路径长度。                       +
                                                                                                                                     +
-------------------------------------------------------------------------------------------+
*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAXV 99
#define INF 32767
typedef struct
{
    int no;                                                                                  //顶点编号
    char info;                                                                             //顶点其他信息
}VertexType;
typedef struct
{
    int edges[MAXV][MAXV];                                                     //邻接矩阵的边数组
    int n, e;                                                                                 //顶点数n和边数e
    VertexType vexs[MAXV];                                                      //存放顶点信息
}MGraph;
typedef struct
{
    int data[MAXV];
    int top;
}SqStack;                                                                                   //创建堆栈结构体
/*-----------------------------------------------------------------------------------------------*/
void Midroad(int path[], int i, int v)
{
    int k;
    SqStack* s;
    s = (SqStack*)malloc(sizeof(SqStack));
    s->top = -1;
    k = path[i];
    while (k != v)
    {
        s->top++;
        s->data[s->top] = k;
        i = k;
        k = path[i];
    }
    while (s->top != -1)
    {
        printf("%d,", s->data[s->top]);
        s->top--;
    }
}
/*-----------------------------------------------------------------------------------------------*/
void Display(int dist[], int path[], int s[], int n, int v)
{
    int i;
    for (i = 0; i < n; i++)
        if (s[i] == 1)
        {
            printf("%d到%d最短路径长为: %d\t路径为:", v, i, dist[i]);
            printf("%d,", v);                                                                            //输出路径上的起点
            Midroad(path, i, v);                                                                      //输出路径上的中间点
            printf("%d\n", i);                                                                          //输出路径上的终点
        }
        else printf("从%d到%d不存在路径\n", v, i);
}
/*-----------------------------------------------------------------------------------------------*/
void Dijkstra(MGraph& g, int v)
{
    int dist[MAXV], path[MAXV];
    int s[MAXV];
    int mindis, i, j, k;
    for (i = 0; i < g.n; i++)
    {
        s[i] = 0;                                                                         //置为空，S【】用来标记是否找到最短路径，为0就没有找到，为1就找到了
        dist[i] = g.edges[v][i];                                                   //距离初始化
        if (g.edges[v][i] < 32767)                                             //v->i 存在路径
            path[i] = v;                                                               //i 的前序节点是v
        else
            path[i] = -1;                                                              //v -> i  不存在路径，i 的前序节点置为 -1
    }
    s[v] = 1;                                                                            //编号v放入s中
    for (i = 1; i < g.n; i++)                                                      //用于求出所有最短路径
    {
        mindis = INF;                                                               // 初始最短长度置为无穷
        k = -1;
        for (j = 0; j < g.n; j++)                                                  //找到所有没找到最短路径的节点
            if (s[j] == 0 && dist[j] < mindis)
            {
                k = j; mindis = dist[j];                                           //最小距离改为dist[j]
            }
        if (k == -1) break;
        s[k] = 1;                                                                        //将最后一个节点加入到s【】数组中，表示全部寻找完毕
        for (j = 0; j < g.n; j++)
            if (s[j] == 0)                                                                 //查找到当前还没有找到最短路径的节点
                if (g.edges[k][j] < 32767 && dist[k] + g.edges[k][j] < dist[j])
                {
                    dist[j] = dist[k] + g.edges[k][j]; 
                    path[j] = k;            //替换j的先驱节点为k
                }
    }
    Display(dist, path, s, g.n, v);                                                 //输出
}
/*-----------------------------------------------------------------------------------------------*/
void start(MGraph* G, int m)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++)
        {
            if (i == j)
                G->edges[i][j] = 0;                                                       //使邻接矩阵全部置0,进行初始化
            else
                G->edges[i][j] = INF;
        }
}
/*-----------------------------------------------------------------------------------------------*/
void main()
{
    MGraph g;
    int i, j, s1, s2, s3;
    printf("***********************************\n    图的单源最短路径求解                  \n***********************************\n\n");
    printf("请输入顶点数n和边数e:\n");
    scanf("%d%d", &i, &j);
    g.n = i;
    g.e = j;
    start(&g, i);                                                                            //初始化邻接矩阵
    for (i = 0; i < g.e; i++)
    {
        printf("输入边的信息：初始节点、终止节点、权值\n");
        scanf("%d%d%d", &s1, &s2, &s3);                                 //储存起始节点  、终止节点  、权值
        g.edges[s1][s2] = s3;                                                      //有向图邻接矩阵关于对角线对称
    }
    srand((unsigned)time(NULL));                                          
    j = rand() % g.n;                                                                
    printf("随机产生的起始点为：%d\n\n", j);
    Dijkstra(g, j);           
    system("pause");
}
