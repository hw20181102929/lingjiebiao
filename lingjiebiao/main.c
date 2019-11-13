#include <stdio.h>
#include <stdlib.h>
#define max 100
int visited[max];
struct ENode
{
    int v1;
    int v2;
};
struct AdjVNode
{
    int AdjV;
    struct AdjVNode * Next;
};
struct VNode
{
    struct AdjVNode * FirstEdge;
};
struct GNode
{
    int Nv;
    int Ne;
    struct VNode G[max];
};
struct GNode * chushihua(int num)
{
    struct GNode *Graph;
    Graph=(struct GNode*)malloc(sizeof(struct GNode));
    Graph->Nv=num;
    Graph->Ne=0;
    for(int i=0;i<Graph->Nv;i++)
    {
        Graph->G[i].FirstEdge=NULL;
    }
    return Graph;
}
void insert(struct GNode *Graph,struct ENode *E)
{
    struct AdjVNode * NewNode;
    NewNode=(struct AdjVNode *)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV=E->v2;
    NewNode->Next=Graph->G[E->v1].FirstEdge;
    Graph->G[E->v1].FirstEdge=NewNode;
    //无向图
    NewNode=(struct AdjVNode *)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV=E->v1;
    NewNode->Next=Graph->G[E->v2].FirstEdge;
    Graph->G[E->v2].FirstEdge=NewNode;
}
void DFS(struct GNode *Graph,int s)
{
    visited[s]=1;
    for(struct AdjVNode * w=Graph->G[s].FirstEdge;w;w=w->Next)
    {
        if(visited[w->AdjV]==0)
        {
            DFS(Graph,w->AdjV);
        }
    }
}
void BFS(struct GNode * Graph,int s)
{
    int p[max];
    int rear=0;
    int front=0;
    visited[s]=1;
    p[++rear]=s;
    while(rear!=front)
    {
        int a=p[++front];
        for(struct AdjVNode * w=Graph->G[a].FirstEdge;w;w=w->Next)
        {
            if(visited[w->AdjV]==0)
            {
                visited[w->AdjV]=1;
                p[++rear]=w->AdjV;
            }
        }
    }
}
int main()
{
    struct GNode *Graph;
    int n;
    scanf("%d",&n);
    Graph=chushihua(n);
    scanf("%d",&Graph->Ne);
    struct ENode * E;
    E=(struct ENode*)malloc(sizeof(struct ENode));
    for(int i=0;i<Graph->Ne;i++)
    {
        scanf("%d %d",&E->v1,&E->v2);
        insert(Graph, E);
    }
    for(int i=0;i<Graph->Nv;i++)
    {
        for(struct AdjVNode * NewNode =Graph->G[i].FirstEdge;NewNode;NewNode=NewNode->Next)
        {
            printf("%d ",NewNode->AdjV);
        }
        printf("\n");
    }
    return 0;
}
