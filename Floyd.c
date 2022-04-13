#include <stdio.h>
#include<stdlib.h>
#define INF 32767
#define MAX 10
int n, m;
struct node
{
    int length;                  //路径长度
    int pre;                     //前序节点
}A[MAX][MAX];
void Floyd()
{
    int k, i, j;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
            {
                if ((A[i][k].length != INF) && (A[k][j].length != INF) && (A[i][k].length + A[k][j].length < A[i][j].length))
                {
                    A[i][j].length = A[i][k].length + A[k][j].length;
                    A[i][j].pre = k;
                }
            }
}
void output()
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            printf("%d ->  %d 的最短距离为: %d\n",i,j,A[i][j].length);
            int k = j;
            printf("路径%d ",i);
            while (A[i][k].pre != i)
            {
                printf("%d",A[i][k].pre);
                k = A[i][k].pre;
            }
            printf("%d\n",j);
        }
}
int main()
{
    printf("******************************************\n    图的任意两点间最短路径求解                  \n******************************************\n\n");
        printf("请输入图的顶点数、边数\n");
        scanf("%d%d",&n,&m);
        int i, j;
        for (i = 0; i < n; i++)                                                     //初始化有向图的邻接矩阵
            for (j = 0; j < n; j++)
            {
                if (i == j) 
                    A[i][j].length = 0;                                               //对角线全为0
                else
                    A[i][j].length = INF;                                        //到其他节点路径长均为无穷
                    A[i][j].pre = i;                   
            }
        int a, b, x;
        printf("请输入初始节点、终止节点、路径长度\n");
        for (i = 0; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &x);
            A[a][b].length = x;
        }
         Floyd();
        output();
        system("pause");
    return 0;
}
