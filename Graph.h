#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999

class Graph{
protected:
	bool m_Type;//0:List 1:Matrix
	int m_Size;
public:
	Graph(bool type, int size);
	~Graph();

	bool getType();
	int getSize();
	virtual int getValue(int i, int j) = 0; //get value 
	virtual void getAdjacentEdges(int vertex, map<int, int>* m) = 0; //adg vertex
	virtual void insertEdge(int from, int to, int weight) = 0; //insert edge
	virtual	bool printGraph(ofstream *fout) = 0; //print
	virtual void insetEdge_nodi(int from, int to, int weight)=0;
	virtual void getAdjacentEdges_nodi(int vertex, map<int, int>* m)=0;
	virtual int getadj(int from, int to)=0;
};

#endif
