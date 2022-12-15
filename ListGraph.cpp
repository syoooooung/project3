#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
	List_nodi=new map < int, int >[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
	delete[]List_nodi;
}
int ListGraph::getValue(int i, int j) {
	return List_nodi[i].find(j)->second; //return wtt
}
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) //get adg
{
	for (map<int, int>::iterator iter = m_List[vertex].begin(); iter != m_List[vertex].end(); iter++)
	{
		m->insert({ iter->first,iter->second });
	}
}

void ListGraph::getAdjacentEdges_nodi(int vertex, map<int, int>* m)
{
	for (map<int, int>::iterator iter = List_nodi[vertex].begin(); iter != List_nodi[vertex].end(); iter++)
	{
		m->insert({ iter->first,iter->second }); //nodirection
	}
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert(make_pair(to, weight));
}
void ListGraph::insetEdge_nodi(int from, int to, int weight) {
	List_nodi[from].insert(make_pair(to, weight));
	List_nodi[to].insert(make_pair(from, weight)); //no direction
}

bool ListGraph::printGraph(ofstream* fout)
{
	*fout << "========PRINT==========" << endl;

	for (int i = 0; i < m_Size; i++)
	{
		cout << "[" << i << "]";
		*fout << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && *fout << " -> "; it_++)
		{
			cout << "(" << it_->first << "," << it_->second << ")";
			*fout << "(" << it_->first << "," << it_->second << ")";
		}
		cout << endl;
		*fout << endl;
	}
	cout << endl;
	*fout <<"===================="<< endl;
	return 1;
}
int ListGraph::getadj(int from, int to){
	map<int, int>::iterator it;
	it = m_List[from].find(to);
	if (it != m_List[from].end() && it->second != 0) { //if connectreturntrue
		return 1; //connect
	}
	else{return 0;}	
}