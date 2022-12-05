#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	char* str=NULL;
	char* str2=NULL;
	char buf[129]={0};

	while(fin.getline(buf, 128))
	{
		char*command = strtok(buf," ");
		if(command==NULL){cout<<"No Command"<<endl; return;}
		if(strcmp(command,"LOAD")==0){
			command=strtok(NULL," ");

			if(!LOAD(command)){
				printErrorCode(100);
			}
			else{
				fout<<"=========LOAD========"<<endl;
				fout<<"Success"<<endl;
				fout<<"====================="<<endl;
			}

		}
		else if(strcmp(command,"PRINT")==0){
			if(!PRINT()){
				printErrorCode(200);
			}
		}

	}	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	int graph_type;
	int j=0;
	ifstream fin_txt;
	fin_txt.open(filename);
	if(!fin_txt){cout<<"fin_txt not open!"<<endl; return 0;}
	char bufff[300]={0};

	fin_txt.getline(bufff, 299); //graph type
	fin_txt.getline(bufff, 299); //graph size
	char * graph_size = strtok(bufff," ");
	string tmp_size = graph_size;
	int sz = atoi(tmp_size.c_str());

	if(strcmp(filename,"graph_L.txt")==0){
		graph_type = 0; //list type num=0;
		graph = new ListGraph(graph_type, sz);
		char from_loc[50] = {0};
		while(fin_txt.getline(bufff, 299)){
			char* vtx_num = strtok(bufff," ");
			char* wtt_num = strtok(NULL, " ");
			if(wtt_num==NULL){
				strcpy(from_loc, vtx_num);
				//string tmp_dd = vtx_num;
				//int from_loc = atoi(tmp_dd.c_str());
			}
			else{
				string str_to = vtx_num;
				string str_wegt= wtt_num;
				int to_vtx = atoi(str_to.c_str());
				int lst_weight = atoi(str_wegt.c_str());

				string tmp_dd = from_loc;
				int from_loc1 = atoi(tmp_dd.c_str());

				graph->insertEdge(from_loc1, to_vtx, lst_weight);
			}
		}


	}
	else if(strcmp(filename,"graph_M.txt")==0){
		graph_type =1; //matrix type_num=1
		graph = new MatrixGraph(graph_type, sz);
		while(fin_txt.getline(bufff,299)){
			char*wt_num = strtok(bufff," "); //weight
			for(int i=0 ; i<sz ; i++){
				string str_wt = wt_num;
				int int_wt = atoi(str_wt.c_str());
				graph->insertEdge(j,i, int_wt);

				wt_num= strtok(NULL, " ");
			}
			j++;
		}
	}
	else{ cout<<"txt name error"<<endl; return 0;}

	return 1;

}

bool Manager::PRINT()
{
	if(graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{

}

bool Manager::mDFS(int vertex)
{

}


bool Manager::mDFS_R(int vertex)
{

}

bool Manager::mDIJKSTRA(int vertex)
{

}

bool Manager::mKRUSKAL()
{

}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{

}

bool Manager::mFLOYD()
{

}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
