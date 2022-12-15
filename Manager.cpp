#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if (load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt) {
	ifstream fin;
	fin.open(command_txt);

	if (!fin)
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	char* str = NULL;
	char* str2 = NULL;
	char buf[129] = { 0 };

	while (fin.getline(buf, 128))
	{
		char* command = strtok(buf, " ");
		if (command == NULL) { cout << "No Command" << endl; return; }
		if (strcmp(command, "LOAD") == 0) {
			command = strtok(NULL, " ");

			if (!LOAD(command)) {
				printErrorCode(100);
			}
			else {
				fout << "=========LOAD========" << endl;
				fout << "Success" << endl;
				fout << "=====================" << endl;
			}

		}
		else if (strcmp(command, "PRINT") == 0) { //commandisprint
			if (!PRINT()) {
				printErrorCode(200);
			}
		}
		else if (strcmp(command, "BFS") == 0) { //commandisbfs
			command = strtok(NULL, " ");
			if (command == NULL) { printErrorCode(300); continue; }
			string tmp_v = command;
			int bfs_vts = atoi(tmp_v.c_str());
			if (!mBFS(bfs_vts)) {
				printErrorCode(300);
			}
		}
		else if (strcmp(command, "DFS") == 0) {//commanddfs
			command = strtok(NULL, " ");
			if (command == NULL) { printErrorCode(400); continue; }
			string tmp_v2 = command;
			int dfs_vts = atoi(tmp_v2.c_str());
			if (!mDFS(dfs_vts)) {
				printErrorCode(400);
			}
		}
		else if (strcmp(command, "DFS_R") == 0) {
			command = strtok(NULL, " ");
			if (command == NULL) { printErrorCode(500); continue; }
			string tmp_v3 = command;
			int dfs_rvts = atoi(tmp_v3.c_str());
			if (!mDFS_R(dfs_rvts)) {
				printErrorCode(500);
			}
		}
		else if(strcmp(command,"KRUSKAL")==0){
			if(!mKRUSKAL()){
				printErrorCode(600);
			}
		}
		else if(strcmp(command, "DIJKSTRA")==0){//commandisdigkstra
			command= strtok(NULL," ");
			if(command==NULL){printErrorCode(700); continue;}
			string tmp_v4 = command;
			int dij = atoi(tmp_v4.c_str());
			if(!mDIJKSTRA(dij)){
				printErrorCode(700);
			}
		}
		else if(strcmp(command,"BELLMANFORD")==0){//commandisbellmanford
			command = strtok(NULL," ");
			string tmp_v5 =command;
			command = strtok(NULL, " ");
			string tmp_v6 = command;
			int st = atoi(tmp_v5.c_str());
			int et = atoi(tmp_v6.c_str());
			if(!mBELLMANFORD(st, et)){
				printErrorCode(800);
			}
		}
		else if(strcmp(command,"FLOYD")==0){//commnadisfloyd
			if(!mFLOYD()){
				printErrorCode(900);
			}
		}
		else if(strcmp(command,"EXIT")==0){//exit

		}

	}
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	int graph_type;
	int j = 0;
	ifstream fin_txt;
	fin_txt.open(filename);
	if (!fin_txt) { cout << "fin_txt not open!" << endl; return 0; }
	char bufff[300] = { 0 };

	fin_txt.getline(bufff, 299); //graph type
	fin_txt.getline(bufff, 299); //graph size
	char* graph_size = strtok(bufff, " "); //graph size
	string tmp_size = graph_size;
	int sz = atoi(tmp_size.c_str());

	if (strcmp(filename, "graph_L.txt") == 0) {//if list
		graph_type = 0; //list type num=0;
		graph = new ListGraph(graph_type, sz);
		char from_loc[50] = { 0 };
		while (fin_txt.getline(bufff, 299)) {
			char* vtx_num = strtok(bufff, " ");
			char* wtt_num = strtok(NULL, " ");
			if (wtt_num == NULL) {
				strcpy(from_loc, vtx_num);
				//string tmp_dd = vtx_num;
				//int from_loc = atoi(tmp_dd.c_str());
			}
			else {
				string str_to = vtx_num;
				string str_wegt = wtt_num; //char*to int
				int to_vtx = atoi(str_to.c_str());
				int lst_weight = atoi(str_wegt.c_str());

				string tmp_dd = from_loc;
				int from_loc1 = atoi(tmp_dd.c_str());

				graph->insertEdge(from_loc1, to_vtx, lst_weight); //insert
				graph->insetEdge_nodi(from_loc1, to_vtx, lst_weight);
			}
		}


	}
	else if (strcmp(filename, "graph_M.txt") == 0) {//if matrix
		graph_type = 1; //matrix type_num=1
		graph = new MatrixGraph(graph_type, sz);
		while (fin_txt.getline(bufff, 299)) {
			char* wt_num = strtok(bufff, " "); //weight
			for (int i = 0; i < sz; i++) {
				string str_wt = wt_num;
				int int_wt = atoi(str_wt.c_str());
				if (graph->getValue(i, j) < int_wt && graph->getValue(i,j)!=0) {
					graph->insertEdge(j, i, int_wt); //insert
					//graph->insetEdge_nodi(j, i, int_wt);
					wt_num = strtok(NULL, " ");
				
				}
				else if (int_wt != 0) {
					graph->insertEdge(j, i, int_wt); //insert
					graph->insetEdge_nodi(j, i, int_wt);
					wt_num = strtok(NULL, " ");
				}
				else {
					graph->insertEdge(j, i, int_wt); //insert
					//graph->insetEdge_nodi(j, i, int_wt);
					wt_num = strtok(NULL, " ");
				}
			}
			j++;
		}
	}
	else { cout << "txt name error" << endl; return 0; }
	fin_txt.close();
	return 1;

}

bool Manager::PRINT()
{
	if(graph == nullptr){
		return 0;
	}
	if (graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if(vertex<0 || vertex > graph->getSize()) return 0;//errorcode
	if (!BFS(graph, vertex, &fout)) {
		return 0;
	}
	return 1;
}

bool Manager::mDFS(int vertex)
{
	if(vertex<0 || vertex > graph->getSize()) return 0;
	if (!DFS(graph, vertex, &fout)) {
		return 0;
	}
	return 1;
}


bool Manager::mDFS_R(int vertex)
{
	if(vertex<0 || vertex > graph->getSize()) return 0; //errorcode
	fout << "=========DFS_R=========" << endl;
	fout << "startvertex: " << vertex << endl;
	vector<bool> visit(graph->getSize(), false); //init
	DFS_R(graph, &visit, vertex, &fout);
	fout << endl;
	fout << "=======================" << endl;
	return 1;
}

bool Manager::mDIJKSTRA(int vertex) //digkstra
{
	if(vertex<0 || vertex > graph->getSize()) return 0;
	if(!Dijkstra(graph, vertex, &fout)){
		return 0;
	}
	else{
		fout<<"==================="<<endl;
	}
	return 1;
}

bool Manager::mKRUSKAL()
{ //kruskal
	if(graph == nullptr){ //if graphnot exist
		return 0;
	}
	if(!Kruskal(graph, &fout)){
		return 0;
	}
	return 1;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex) //bellmanford
{
	if(!Bellmanford(graph,s_vertex, e_vertex,&fout)){
		return 0; //errorcode
	}
	return 1;
}

bool Manager::mFLOYD()
{
	if(!FLOYD(graph, &fout)){
		return 0; //errorcode
	}
	return 1;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}
