#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex, ofstream* fout)
{
    if (graph == NULL)return 0;
    int sz = graph->getSize();
    int* bfs_arr = new int[sz];
    for (int i = 0; i < sz; i++) {
        bfs_arr[i] = 0;           //initializaion
    }
    map<int, int> mm;
    map<int, int>::iterator i;
    queue<int> q;
    q.push(vertex);
    bfs_arr[vertex] = 1;
    *fout << "========BFS========" << endl;
    *fout << "startvertex: " << vertex << endl;
    while (!q.empty()) {
        vertex = q.front();
        graph->getAdjacentEdges_nodi(vertex, &mm);
        *fout << vertex;
        q.pop();
        for (i = mm.begin(); i != mm.end(); i++) {
            if (!bfs_arr[i->first]) {
                q.push(i->first);
                bfs_arr[i->first] = 1;
            }
        }
        if (!q.empty()) { *fout << " -> "; }
    }
    *fout << endl;
    *fout << "=================" << endl;
    delete[] bfs_arr;
    return 1;
}

bool DFS(Graph* graph, int vertex, ofstream* fout)
{
    if (graph == NULL)return 0;
    int sz = graph->getSize();
    int* bfs_arr = new int[sz];
    for (int i = 0; i < sz; i++) {
        bfs_arr[i] = 0;           //initializaion
    }
    map<int, int> mm;
    map<int, int>::iterator i;
    stack<int> s;
    s.push(vertex);
    bfs_arr[vertex] = 1;
    *fout << "========DFS========" << endl;
    *fout << "startvertex: " << vertex << endl;
    while (!s.empty()) {
        vertex = s.top();
        graph->getAdjacentEdges_nodi(vertex, &mm);
        *fout << vertex;
        s.pop();
        for (i = mm.end(); i != mm.begin();) {
            i--;
            if (!bfs_arr[i->first]) {
                s.push(i->first);
                bfs_arr[i->first] = 1;
            }
        }
        if (!s.empty()) { *fout << " -> "; }
    }
    *fout << endl;
    *fout << "=================" << endl;
    delete[] bfs_arr;
    return 1;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream* fout)
{
    map<int, int> mm;
    visit->at(vertex) = true;
    *fout << vertex;
    map<int, int>::iterator i;
    graph->getAdjacentEdges_nodi(vertex, &mm);
    for (i = mm.begin(); i != mm.end(); i++) {
        if (!visit->at(i->first)) {
            *fout << " -> ";
            DFS_R(graph, visit, i->first, fout);
        }
    }
    return 1;
}

bool Kruskal(Graph* graph)
{
    return 1;
}

bool Dijkstra(Graph* graph, int vertex, ofstream* fout)
{
    *fout << "======Dijkstra========" << endl;
    int* distance = new int[graph->getSize()];
    int* visit = new int[graph->getSize()];
    int* path = new int[graph->getSize()];

    for (int i = 0; i < graph->getSize(); i++) {
        distance[i] = INT_MAX;
        visit[i] = 0;
        path[i] = -1;
    }
    map<int, int> mm;
    map<int, int>::iterator i;
    stack<int> s;
    s.push(vertex);
    distance[vertex] = 0;
    int vsit_n;
    while (1) {
        vsit_n = s.top();
        visit[vsit_n] = 1;
        s.pop();

    }
    return 1;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{
    return 1;
}

bool FLOYD(Graph* graph)
{
    return 1;
}