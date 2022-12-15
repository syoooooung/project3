#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex, ofstream* fout)
{
    if (graph == NULL)return 0;
    int sz = graph->getSize();
    int* bfs_arr = new int[sz];
    for (int i = 0; i < sz; i++) {
        bfs_arr[i] = 0;       //initializaion
    }
    map<int, int> mm;
    map<int, int>::iterator i;
    queue<int> q;


    q.push(vertex); //fist, input vertex=>queuefornt 
    bfs_arr[vertex] = 1; //visit==true
    *fout << "========BFS========" << endl;
    *fout << "startvertex: " << vertex << endl;
    while (!q.empty()) { //loop queue is empty
        vertex = q.front();
        graph->getAdjacentEdges_nodi(vertex, &mm); //find adjacent vertex
        *fout << vertex;
        q.pop();
        //*out<<vertex;
        for (i = mm.begin(); i != mm.end(); i++) {
            if (!bfs_arr[i->first]) {
                q.push(i->first); //if not visit=> queuepush
                bfs_arr[i->first] = 1; //and visit=1
            }
        }
        if (!q.empty()) { *fout << " -> "; }
    }
    *fout << endl;
    *fout << "=================" << endl;
    delete[] bfs_arr;
    return 1;
}

bool DFS(Graph* graph, int vertex, ofstream* fout)
{
    if (graph == NULL)return 0;
    int sz = graph->getSize();
    int* bfs_arr = new int[sz];
    for (int i = 0; i < sz; i++) {
        bfs_arr[i] = 0;     //initializaion
    }
    map<int, int> mm;
    map<int, int>::iterator i;
    stack<int> s; //dfs using stack
    s.push(vertex); //push vertex1
    bfs_arr[vertex] = 1; //visit check
    *fout << "========DFS========" << endl;
    *fout << "startvertex: " << vertex << endl;
    while (!s.empty()) { //loop empty
        vertex = s.top();
        graph->getAdjacentEdges_nodi(vertex, &mm); //get adjancentvertex
        *fout << vertex;
        s.pop(); //print and pop
        for (i = mm.end(); i != mm.begin();) {
            i--;
            if (!bfs_arr[i->first]) {
                s.push(i->first);
                bfs_arr[i->first] = 1;
            }
        }
        if (!s.empty()) { *fout << " -> "; }
    }
    *fout << endl;
    *fout << "=================" << endl;
    delete[] bfs_arr;
    return 1;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream* fout)
{
    map<int, int> mm; //dfs using recursion
    visit->at(vertex) = true;
    *fout << vertex;
    map<int, int>::iterator i;
    graph->getAdjacentEdges_nodi(vertex, &mm); //get adjacent vertex
    for (i = mm.begin(); i != mm.end(); i++) {
        if (!visit->at(i->first)) { //if not visit
            *fout << " -> ";
            DFS_R(graph, visit, i->first, fout); //recursion
        }
    }
    return 1;
}

bool Kruskal(Graph* graph,ofstream *fout)
{
    if (graph == NULL)return 0;
    int g_sz= graph->getSize();
    int path[g_sz][g_sz] ={0,};
    int edge[g_sz][g_sz]={0,};
    int parent[g_sz]={0,};
    for(int i=0; i<g_sz; i++){
        for(int j=0; j<g_sz; j++){ //initialization
            path[i][j]=0;
            edge[i][j]=0;
            parent[i]=-1;
        }
    }


    for(int i=0; i<g_sz; i++){
        map<int,int>mm;
        map<int,int>::iterator it;
        graph->getAdjacentEdges(i, &mm); //getadjacent&no direction

        for(it = mm.begin() ; it!= mm.end();it++){
            path[i][it->first]= it->second;
            int tmp_n1=path[i][it->first]; //remove one because nodirection
            int tmp_n2=path[it->first][i];
            if(tmp_n1==tmp_n2){ 
                path[i][it->first]=0; //if same=>one remove
                continue;
            }
            else if((tmp_n1 > tmp_n2 )&& (tmp_n2 != 0)){ //smaller save
                path[i][it->first]=0; continue;
            }
            else if((tmp_n1 < tmp_n2) &&( tmp_n1 != 0)){ //smaller save
                path[it->first][i]=0; continue;
            }
        } //no isang
    }
    int weight[g_sz*g_sz]={0,};
    int w_index=1;
    for(int i=0; i<g_sz; i++){
        for(int j=0; j<g_sz;j++){
            if(path[i][j] != 0){
                weight[w_index]=path[i][j]; //copy weight to arr
                w_index++;
            }
        }
    }
    ///---------------
    

    quicksort(weight,1,w_index-1); //weight sort

    for(int i=0;i< w_index;i++){
        weight[i]=weight[i+1]; //shift left 1
    }
    w_index--;
    for(int i=0; i<w_index; ){
        for(int j=0; j<g_sz; j++){
            for(int k=0; k<g_sz; k++){
                if(path[j][k]== weight[i]){ //find edge
                    path[j][k]=0; //check visit
                    int k_set = CollapsingFind(parent, k);
                    int j_set = CollapsingFind(parent, j);
                    if(k_set != j_set){ //if diff set
                        Union(k_set, j_set, parent); //union
                        edge[j][k]= weight[i];
                    }
                    i++; 
                    if(i==w_index)break;
                }
                if(i==w_index)break; //break
            }
            if(i==w_index)break;
        }
         if(i==w_index)break;
    }

//
    for(int i=0; i<g_sz ; i++){
        for(int j=0; j<g_sz; j++){
            if(edge[i][j]!=0){
                edge[j][i]=edge[i][j]; //copy
            }
        }
    }
    
    *fout<<"======= Kruskal ======="<<endl;
    int distance=0;
    for(int i=0; i<g_sz; i++){
        *fout<<"["<<i<<"] "; 
        for(int j=0; j<g_sz; j++){
            if(edge[i][j]!=0){
                *fout<<j<<"("<<edge[i][j]<<") "; //print
                distance += edge[i][j]; //count distance
            }
        }
        *fout<<endl;
    }
    *fout<<"cost: "<<distance<<endl;
    *fout<<"========================"<<endl;
    return 1;
}
int CollapsingFind(int parent[], int i){
    int r=i;
    for(r=i ; parent[r]>=0; r=parent[r]){ //get parent
        while(i !=r){
            int s= parent[i]; //collapsing find
            parent[i]=r;
            i=s;
        }
    }
    return r;
}
int Union(int i, int j, int parent[]){
    int temp = parent[i]+ parent[j];
    if(parent[i]> parent[j]){ //if i smaller
        parent[i]=j; //put i to j
        parent[j]=temp;
    }
    else{
        parent[j]=i; //put j to i
        parent[i]=temp;
    }
}
void quicksort(int arr[], int low, int high){ //sort function
    if(low<high){
        if(high-low+1 <=6){
            insertionsort(arr,low,high); //segmetation smaller6
        }
        else{
            int i= low;
            int j= high+1;
            int pivot=arr[low];
            do{
                do{i++;}while(arr[i]<pivot); //find bigger num
                do{j--;}while(arr[j]>pivot); //find smaller num
                if(i<j){int tmp=arr[i]; arr[i]=arr[j]; arr[j]=tmp;} //swap
            }while(i<j);
            int tmp= arr[low];
            arr[low]=arr[j]; //swap
            arr[j]= tmp;

            quicksort(arr,low,j-1); //recursion
            quicksort(arr,j+1,high);
        }
    } 
}
void insertionsort(int arr[],int a, int e ){//low, high
    for(int j=2; j<=e;j++){
        int insert_n= arr[j];
        int i=j-1;
        arr[0]= insert_n; //tempsave
        while(insert_n<arr[i]){
            arr[i+1]=arr[i]; //cmp and shift
            i--;
        }
        arr[i+1]=insert_n;
    }
}
bool Dijkstra(Graph* graph, int vertex, ofstream* fout)
{
    *fout << "======Dijkstra========" << endl;
    int* distance = new int[graph->getSize()];
    int* visit = new int[graph->getSize()];
    int* path = new int[graph->getSize()];

    for (int i = 0; i < graph->getSize(); i++) {
        distance[i] = 0;
        visit[i] = 0; //initialization
        path[i] = -1;
    }
    map<int, int> mm;
    map<int, int>::iterator it;
    graph->getAdjacentEdges(vertex, &mm);//get adjacent vertex

    distance[vertex] = 0; //init vertex distance
    stack<int> s;
    s.push(vertex); //push stack vertex1
    int pre_i;
    int g_sz = graph->getSize();
    while (!s.empty()) {
        pre_i = s.top(); //save top
        visit[pre_i] = 1; //visit
        s.pop(); //top pop

        for (int i = 0; i < g_sz; i++) {
            if (i != vertex && graph->getadj(pre_i, i) == 1 && i != pre_i) {
                if (visit[i] == 0) {
                    s.push(i); //if not visit=>push
                }
                if ((distance[i] != 0 && distance[i] > (distance[pre_i] + graph->getValue(pre_i, i))) || distance[i] == 0) {
                    distance[i] = distance[pre_i] + graph->getValue(pre_i, i); //put short distance
                    path[i] = pre_i; //change path
                }

            }
        }
    }

    *fout << "startvertex : " << vertex << endl;
    int pre;
    for (int i = 0; i < graph->getSize(); i++) {
        if (i == vertex) { //not print input vertex
            continue;
        }
        pre = i;
        stack<int> s;

        //int pre_node
        *fout << "[" << i << "] ";
        while (1) { //loop path=>-1
            if (path[pre] == -1) {
                break;
            }
            s.push(path[pre]);
            pre = path[pre];
        }
        if (s.empty()) { //if empty=>print x
            *fout << "x" << endl;
            continue;
        }
        while (!s.empty()) { //print
            *fout << s.top() << "-> ";
            s.pop();
        }
        *fout << i << "[" << distance[i] << "]" << endl;
    }
    return 1;
}

int minDistance(Graph* graph, int* dist, int* visit, int sz) {
    int min = INT_MAX, min_index;
    map<int, int> mm;
    for (int v = 0; v < sz; v++) {
        if (!visit[v] && min >= dist[v]) { //if min>dist[v]
            min_index = v;
            min = dist[v]; //min=distance v
        }
    }
    return min_index;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream* fout)
{
    if (graph->getSize() == 0) { *fout << "no graph" << endl; return 0; }
    if  (s_vertex <0 || s_vertex>=graph->getSize() || e_vertex <0 || e_vertex>=graph->getSize() ) return 0;
    int* distance = new int[graph->getSize()];
    int* visit = new int[graph->getSize()];
    int* path = new int[graph->getSize()];
   // vector<vector<int>> path(graph->getSize(), vector<int>(graph->getSize(), INT_MAX));
    int g_sz = graph->getSize();
    bool Is_neg_cycle;
    int weigh_0;
   
    map<int, int>::iterator it;
    for (int i = 0; i != g_sz; i++) { //initialization
        distance[i] = INT_MAX;
        visit[i] = 0;
        path[i] = INT_MAX;
        //path[i][0] = s_vertex;
    }
    distance[s_vertex] = 0;
   
    for (int i = 0; i < g_sz; i++) { //loop vertex num
        Is_neg_cycle = false; //negative cycle check
        int j = s_vertex;
       //for (int j = 0; j < g_sz; j++) {
        int p = 0;
        while (p<g_sz) {
            map<int, int> mm;
            graph->getAdjacentEdges(j, &mm);
            for (it = mm.begin(); it != mm.end(); it++) {
                int cur_v = it->first; //jto cur_v 
                int weit = it->second; //j to cur_v => weight

                if (distance[j] != INT_MAX && distance[cur_v] > distance[j] + weit) {
                    distance[cur_v] = distance[j] + weit;
                    if(i== g_sz-1 )Is_neg_cycle = true; //negative cycle

                    path[cur_v] = j;
                }
                else if((distance[cur_v]> distance[j]+ weit) && (i==g_sz-1)){
                    Is_neg_cycle = true;
                }
            }
            if (j + 1 == g_sz) { j = 0; continue; } //turntostart
            j++;
            p++;
            //}
        }
    }
    if (Is_neg_cycle==true) { //errorcode
        return 0;
    }
    for (int i = 0; i < g_sz; i++) {
        //if(distance[i]<0) return 0;
    }
    stack<int> s;
    s.push(e_vertex);
    int sum = distance[e_vertex];
    ///if(sum==INT_MAX || sum <= 0)return 0;
    int pre_n = path[e_vertex];
    while (pre_n!= INT_MAX) {
        s.push(pre_n);
        pre_n = path[pre_n];
    }
    s.push(s_vertex);
    *fout << "======= Bellman-Ford =======" << endl;
    s.pop();
    while (!s.empty()) { //loop stackisempty
        *fout << s.top();
        s.pop();
        if (!s.empty())*fout << "->";
         
    }
    *fout << endl << "cost: " << sum << endl;
    *fout << "=============================" << endl;

    return 1;
}

bool FLOYD(Graph* graph,ofstream *fout)
{
    int g_sz = graph->getSize();
    int distance[g_sz][g_sz]={0,};
    for(int i=0 ; i<g_sz ; i++){
        for(int j=0; j<g_sz ; j++){
            distance[i][j]=99999;
            if(i==j) distance[i][j]=0; //initialization
        }
    }
    for(int i=0; i< g_sz; i++){
        map<int, int> mm;
        map<int, int>::iterator it;
        graph->getAdjacentEdges(i, &mm);
        for(it = mm.begin();it != mm.end(); it++){ //push value
            distance[i][it->first]= it->second;
        }
    }

    for(int i=0 ; i<g_sz ; i++){
        for(int j=0; j<g_sz ; j++){ //dia put 0
            if(i==j) distance[i][j]=0;
        }
    }

    for(int k=0; k< g_sz; k++){
        for(int i=0; i<g_sz; i++){
            for(int j=0; j< g_sz ; j++){ //put short distance
                if(distance[i][k]+ distance[k][j]<distance[i][j] ){
                    distance[i][j]= distance[i][k]+ distance[k][j];
                }
            }
        }
    }
    for(int i=0; i< g_sz ; i++){
       if(distance[i][i]<0) return 0; //negative cycle
    }
    cout<<"1";
    *fout<<"======== PRINT ========="<<endl; //print matrix
    for (int i = 0; i < g_sz; i++)
	{
		*fout << "[" << i << "]" << '\t';
	}
    *fout<<endl;
    for(int i=0; i<g_sz; i++){
        *fout<<"["<<i<<"]"<<"\t";
        for(int j=0; j<g_sz  ; j++){
            if(distance[i][j]==99999&& i!=j){
                *fout<<"x"<<"\t";
            }
            else{
                *fout<<distance[i][j]<<"\t";
            }
        }
        *fout<<endl;
    }
    *fout<<"====================="<<endl;


    return 1;
}