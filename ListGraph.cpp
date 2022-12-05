#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{

}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert(make_pair(to, weight));
}

bool ListGraph::printGraph(ofstream *fout)
{
	cout<<"Graph is ListGraph!"<<endl;
	*fout<<"Graph is ListGraph!"<<endl;

	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]";
		*fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout<<" -> "; it_++)
		{
			cout<<"("<<it_->first<<","<<it_->second<<")";
			*fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		cout<<endl;
		*fout<<endl;
	}
	cout<<endl;
	*fout<<endl;
	return 1;
}