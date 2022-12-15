#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) //constructor
{
	m_Mat = new int* [size];
	Mat_nodi = new int*[size];
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		Mat_nodi[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int) * size);
		memset(Mat_nodi[i], 0, sizeof(int) * size);
	}
}

MatrixGraph::~MatrixGraph() //destructor
{
	for (int i = 0; i < getSize(); i++)
	{
		delete[] m_Mat[i];
		delete[] Mat_nodi[i];
	}
	delete[] m_Mat;
	delete[] Mat_nodi;
}

int MatrixGraph::getValue(int i, int j) {
	return Mat_nodi[i][j];
}
int MatrixGraph::getadj(int from, int to){
	if (m_Mat[from][to] != 0) {
		return true; //connect
	}
	else{return false;}
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) //get adjacent vertex
{
	for (int i = 0; i < getSize(); i++)
	{
		if (m_Mat[vertex][i] != 0) {
			m->insert({ i, m_Mat[vertex][i] });
		}
	}
}

void MatrixGraph::getAdjacentEdges_nodi(int vertex, map<int, int>* m) {
	for (int i = 0; i < getSize(); i++) //no direction
	{
		if (Mat_nodi[vertex][i] != 0) {
			m->insert({ i, Mat_nodi[vertex][i] });
		}
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight;
}

void MatrixGraph::insetEdge_nodi(int from, int to, int weight) {
	Mat_nodi[from][to] = weight; //no direction
	Mat_nodi[to][from] = weight;
}

bool MatrixGraph::printGraph(ofstream* fout)
{
	if (m_Size < 0)
		return 0;

	*fout << "======== PRINT ========" << endl;

	cout << '\t';
	*fout << "\t";
	for (int i = 0; i < m_Size; i++) //print
	{
		cout << "[" << i << "]" << '\t';
		*fout << "[" << i << "]" << '\t';
	}
	cout << endl;
	*fout << endl;

	for (int i = 0; i < m_Size; i++)
	{
		cout << "[" << i << "]"; //vertex print
		*fout << "[" << i << "]";
		for (int j = 0; j < m_Size && *fout << "\t"; j++)
		{
			cout << m_Mat[i][j];
			*fout << m_Mat[i][j];
		}
		cout << endl;
		*fout << endl;
	}
	*fout<<"========================"<<endl;
	return 1;
}
