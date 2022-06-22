#include<iostream>
#include <list>
using namespace std;
#define MIN -1

class Graph
{
    list<int> *list_adjecent;
    int vertice;
    void func(int u, bool visited[], int D[], int L[], int anc[], bool A[]){
    visited[u] = true;
    int child= 0;
    static int t= 0;
    D[u] = L[u] = ++t;
    list<int>::iterator it;
    for (it = list_adjecent[u].begin(); it != list_adjecent[u].end(); ++it)
    {
        int v = *it;
        if (!visited[v])
        {
            child++;
            anc[v] = u;
            func(v, visited, D, L, anc, A);
            L[u]  = min(L[u], L[v]);
            if (anc[u] == MIN && child> 1)
		{
               A[u] = true;
		}
            if (anc[u] != MIN && L[v] >= D[u])
		{
               A[u] = true;
		}
        }
        else if (v != anc[u])
		{
            L[u]  = min(L[u], D[v]);
		}
    }
}

public:
   Graph(int vertice){
    this->vertice = vertice;
    list_adjecent = new list<int>[vertice];
}
    void edgeAdd(int v, int w){
    list_adjecent[v].push_back(w);
    list_adjecent[w].push_back(v);
}
    void CutVertex(){
    int *D = new int[vertice];
    int *L = new int[vertice];
    int *anc = new int[vertice];
    bool *visited = new bool[vertice];
    bool *A = new bool[vertice];
    for (int it = 0; it < vertice; it++)
    {
        anc[it] = MIN;
        visited[it] = false;
        A[it] = false;
    }
    for (int it = 0; it < vertice; it++)
	{
        if (visited[it] == false)
		{
            func(it, visited, D, L, anc, A);
		}
	}

    for (int it = 0; it < vertice; it++)
	{
        if (A[it] == true)
		{
            cout << it << " ";
		}
	}
}

};

int main()
{
    int v,e,a,b;
    cout<< "Enter number of vertices:";
    cin>> v;
    cout<< "Enter number of edges:";
    cin>> e;
    cout<< "Enter the edges:";
    Graph g(v);
    for(int i = 0; i < e;i++) {
        cin>> a;
        cin>>b;
        g.edgeAdd(a,b);
    }
    cout<< "The cut vertex is:";
    g.CutVertex();

    return 0;
}
