#include<stdio.h>
using namespace std;
int tsort[1000000];
int top = 0;
class EdgeNode
{
public:
    int adjvex;
    int weight;
    EdgeNode* next;
};
enum Status{Undiscovered, Discovered, Visited};
class VertexNode
{
public:
    Status status = Undiscovered;
    int distance = 0;
    EdgeNode* firstedge = NULL;
    int dtime, ftime;
};
void DFS(VertexNode* V, int v, int &time)
{
    V[v].dtime = ++time; V[v].status = Discovered;
    EdgeNode* n = V[v].firstedge;
    while(n != NULL)
    {
        if(V[n->adjvex].status == Undiscovered)
        {
            DFS(V, n->adjvex, time);
        }
        n = n->next;
    }
    V[v].status = Visited; V[v].ftime = ++time;
    tsort[top] = v; top++;
}
int main()
{
    int n, m;
    int u, v, w;
    int time = 0;
    EdgeNode* e;
    scanf("%d %d", &n, &m);
    VertexNode* V = new VertexNode[n+1];
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        e = new EdgeNode;
        e->adjvex = v;
        e->next = V[u].firstedge;
        e->weight = w;
        V[u].firstedge = e;
    }
    for(int i = 1; i <= n; i++)
    {
        if(V[i].status == Undiscovered)
        {
            DFS(V, i, time);
        }
    }
    top--;
    int max_weight = 0;
    for(int i = top; i >= 0; i--)
    {
        e = V[tsort[i]].firstedge;
        while(e != NULL)
        {
            if(V[e->adjvex].distance < V[tsort[i]].distance + e->weight)
            {
                V[e->adjvex].distance = V[tsort[i]].distance + e->weight;
            }
            if(V[e->adjvex].distance > max_weight) max_weight = V[e->adjvex].distance;
            e = e->next;
        }
    }
    printf("%d", max_weight);
    return 0;
}
