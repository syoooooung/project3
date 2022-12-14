#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	map < int, int >* m_List;
	map < int, int >* List_nodi;
public:	
	ListGraph(bool type, int size);
	~ListGraph();
		
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void getAdjacentEdges_nodi(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	void insetEdge_nodi(int from, int to, int weight);
	bool printGraph(ofstream *fout);
	int getValue(int i, int j);
	int getadj(int from, int to);
};

#endif