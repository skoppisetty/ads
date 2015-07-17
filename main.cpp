#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iostream>
#include <queue>


#include <time.h>


using namespace std;
#include "dijikstra.h"

// returns true if its a connected graph else false
bool is_connected(unordered_map<int, unordered_map<int,int>>& G, int n){
	bool connected = false;
	int visited[n];	
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}

	int start_vertex = 0;
	int next_vertex;
	queue<int> temp;

	if (visited[start_vertex] != 1)
	{
		temp.push(start_vertex);
		while(!temp.empty())
		{
			next_vertex = temp.front();
			temp.pop();
			visited[next_vertex] = 1;
			for (auto it = G[next_vertex].begin(); it != G[next_vertex].end(); ++it )
			{
				if(visited[it->first] != 1)
				{
					temp.push(it->first);
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (visited[i] != 1)
		{
			return false;
		}
	}
	return true;
}

void generate_randomgraph(unordered_map<int, unordered_map<int,int>> & G, int n, double d){
	double max_edges = (n * (n-1))/2;
	int num_edges = ceil((d * max_edges)/100);
	if(num_edges < n-1){
		cout << "not possible" << endl;
		exit(1);
	}

	//adjacency list of a graph
	do{
		int num = 0;
		G.clear();

		while (num != num_edges) {
			int s = rand() % n;
			int d = rand() % n;
			int ecost = (rand() % 1000) + 1;
			if (s == d)
				continue;

			//cout << "random" << endl;

			// check for edge 
			unordered_map<int,int>::const_iterator got = G[s].find (d);
			if(got == G[s].end()){
				//cout << "added edge "<< s << " " << d << endl;
				G[s][d]=ecost;
				G[d][s]=ecost;
				num++;

			}

		}
	}while(!is_connected(G,n));
	cout << "Generated random graph" << endl;
}


void prep_dijikstra(unordered_map<int, unordered_map<int,int>> & G, int m, int n, int src, type method, int mode){
		vector<int> spath;
		for(int i = 0; i < m ; i++){
			int sval = 0;
			spath = dijikstra(G,src,i,method);  // Run dijkstra to find shortest path
			
			// traverse through shortest path to find path weight
			// cout << "source :"<< src << " Dest: " << i << "		";
			if(spath.empty()){
				// cout << "0" << endl;
				continue;
			}
			for(int i=0;i< spath.size()-1;i++){ 
				int s=spath[i];
				int d=spath[i+1];
				sval += G[s][d];
			}
			if(mode == 1){
				cout << sval << endl;   // Print the path weight
			}
			// for(int i=0; i < spath.size(); i++){ // print the path
			// 	cout << spath[i] << " "; 
			// }
		}
}

void read_file(unordered_map<int, unordered_map<int,int>> & G, int &m, int &n, int &src, string filename){
	 
	ifstream myfile(filename);
	myfile >> src; 		
	myfile >> m;
	myfile >> n;		

	// adjacency list - a matrix with G[a][b] = c
	// indicates that the edge between a to b with cost c.
	// unordered_map<int, unordered_map<int,int>> G; 
	int a,b,c;
	while (myfile >> a){   // populate the adjacency lists
		myfile >> b >> c;
		G[a][b]=c;
		G[b][a]=c;
	}

}

int main(int argc, char *argv[]){
	unordered_map<int, unordered_map<int,int>> G;
	int src,m,n; 
	type method;
	if(string(argv[1]) == "-r"){
		// perfomrnace mode
		m = atoi(argv[2]);
		double d = atof(argv[3]);
		src = atoi(argv[4]);
		generate_randomgraph(G,m,d);
		clock_t Start_fib, Time_fib;
		clock_t Start_left, Time_left;
		Start_fib = clock();
		prep_dijikstra(G,m,n,src,fib,0);
		Time_fib = clock() - Start_fib;
		Start_left = clock();
		prep_dijikstra(G,m,n,src,leftist,0);
		Time_left = clock() - Start_left;

		cout << "Execution time for fibonacci heap: " << Time_fib << endl;
		cout << "Execution time for Leftist tree: " << Time_left << endl;


	}
	else if(string(argv[1]) == "-f"){
		string filename=argv[2];
		read_file(G,m,n,src,filename);
		method = fib;
		prep_dijikstra(G,m,n,src,method,1);
	}
	else{
		string filename=argv[2];
		read_file(G,m,n,src,filename);
		method = leftist;
		prep_dijikstra(G,m,n,src,method,1);
	}	
}