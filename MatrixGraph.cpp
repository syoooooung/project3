#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{

}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
		m_Mat[from][to]=weight;
}

bool MatrixGraph::printGraph(ofstream *fout)
{
	if( m_Size < 0 )
		return 0;

	cout<<"Graph is MatrixGraph!"<<endl;
	*fout<<"Graph is MatrixGraph!"<<endl;

	cout<<'\t';
	*fout<<"\t";
	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]"<<'\t';
		*fout<<"["<<i<<"]"<<'\t';
	}
	cout<<endl;
	*fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]";
		*fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && *fout<<"\t"; j++)
		{
			cout<<m_Mat[i][j];
			*fout<<m_Mat[i][j];
		}
		cout<<endl;
		*fout<<endl;
	}
	return 1;
}
