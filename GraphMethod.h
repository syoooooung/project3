#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
#define INT_MAX 2147483647

bool BFS(Graph* graph, int vertex,ofstream *fout); //bfs
bool DFS(Graph* graph, int vertex,ofstream *fout);
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex,ofstream *fout);
bool Kruskal(Graph* graph,ofstream *fout);
void quicksort(int arr[], int low, int high);
void insertionsort(int arr[],int a, int e );
int CollapsingFind(int parent[], int i);
int Union(int i, int j, int parent[]);
bool Dijkstra(Graph* graph, int vertex,ofstream *fout);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex,ofstream *fout);
bool FLOYD(Graph* graph,ofstream *fout);
int minDistance( int *dist, int *visit, int sz); //minimum distance return function
#endif
