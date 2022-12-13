#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	int** m_Mat;
	int** Mat_nodi;

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();	
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printGraph(ofstream *fout);

	void insetEdge_nodi(int from, int to, int weight);
	void getAdjacentEdges_nodi(int vertex, map<int, int>* m);
	int getValue(int i, int j);
};

#endif