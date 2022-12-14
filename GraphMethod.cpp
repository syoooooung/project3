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
        distance[i] = 0;
        visit[i] = 0;
        path[i] = -1;
    }
    map<int, int> mm;
    map<int, int>::iterator it;
    graph->getAdjacentEdges(vertex, &mm);

    distance[vertex] = 0;
    stack<int> s;
    s.push(vertex);
    int pre_i;
    int g_sz = graph->getSize();
    while (!s.empty()) {
        pre_i = s.top();
        visit[pre_i] = 1;
        s.pop();

        for (int i = 0; i < g_sz; i++) {
            if (i != vertex && graph->getadj(pre_i, i) == 1 && i != pre_i) {
                if (visit[i] == 0) {
                    s.push(i);
                }
                if ((distance[i] != 0 && distance[i] > (distance[pre_i] + graph->getValue(pre_i, i))) || distance[i] == 0) {
                    distance[i] = distance[pre_i] + graph->getValue(pre_i, i);
                    path[i] = pre_i;
                }

            }
        }
    }

    *fout << "startvertex : " << vertex << endl;
    int pre;
    for (int i = 0; i < graph->getSize(); i++) {
        if (i == vertex) {
            continue;
        }
        pre = i;
        stack<int> s;
        *fout << "[" << i << "] ";
        while (1) {
            if (path[pre] == -1) {
                break;
            }
            s.push(path[pre]);
            pre = path[pre];
        }
        if (s.empty()) {
            *fout << "x" << endl;
            continue;
        }
        while (!s.empty()) {
            *fout << s.top() << "-> ";
            s.pop();
        }
        *fout << i << "[" << distance[i] << "]" << endl;
    }
    return 1;
}

int minDistance(Graph* graph, int* dist, int* visit, int sz) {
    int min = INT_MAX, min_index;
    map<int, int> mm;
    for (int v = 0; v < sz; v++) {
        if (!visit[v] && min >= dist[v]) {
            min_index = v;
            min = dist[v];
        }
    }
    return min_index;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream* fout)
{
    if (graph->getSize() == 0) { *fout << "no graph" << endl; return 0; }

    int* distance = new int[graph->getSize()];
    int* visit = new int[graph->getSize()];
    int* path = new int[graph->getSize()];
   // vector<vector<int>> path(graph->getSize(), vector<int>(graph->getSize(), INT_MAX));
    int g_sz = graph->getSize();
    bool Is_neg_cycle;
    int weigh_0;
   
    map<int, int>::iterator it;
    for (int i = 0; i != g_sz; i++) {
        distance[i] = INT_MAX;
        visit[i] = 0;
        path[i] = INT_MAX;
        //path[i][0] = s_vertex;
    }
    distance[s_vertex] = 0;
   
    for (int i = 0; i < g_sz; i++) {
        Is_neg_cycle = 0;
        int j = s_vertex;
       //for (int j = 0; j < g_sz; j++) {
        int p = 0;
        while (p<g_sz) {
            map<int, int> mm;
            graph->getAdjacentEdges(j, &mm);
            for (it = mm.begin(); it != mm.end(); it++) {
                int cur_v = it->first; //j에서 cur_v 를 볼거야
                int weit = it->second; //j에서 cur_v로의 가중치

                if (distance[j] != INT_MAX && distance[cur_v] > distance[j] + weit) {
                    distance[cur_v] = distance[j] + weit;
                    Is_neg_cycle = 1;

                    path[cur_v] = j;
                }
            }
            if (j + 1 == g_sz) { j = 0; continue; }
            j++;
            p++;
            //}
        }
    }
    if (Is_neg_cycle) {
        return 0;
    }
    for (int i = 0; i < g_sz; i++) {
        cout << path[i] << " " << distance[i] << endl;
    }
    stack<int> s;
    s.push(e_vertex);
    int sum = distance[e_vertex];
    int pre_n = path[e_vertex];
    while (pre_n!= INT_MAX) {
        s.push(pre_n);
        pre_n = path[pre_n];
    }
    s.push(s_vertex);
    *fout << "======= Bellman-Ford =======" << endl;
    s.pop();
    while (!s.empty()) {
        *fout << s.top();
        s.pop();
        if (!s.empty())*fout << "->";
         
    }
    *fout << endl << "cost: " << sum << endl;
    *fout << "=============================" << endl;

    return 1;
}

bool FLOYD(Graph* graph)
{
    return 1;
}