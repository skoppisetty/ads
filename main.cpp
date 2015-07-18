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


/**
* checks whether the graph is connected or not
*
*  This function takes in the adjacency list and number of vertices and 
*  checks whether the graph represented by the adjacency list is connected or not.
*
* @param G
*   Adjacency list as unordered_map<int, unordered_map<int,int>>&
* @param int
*   number of vertices
*
* @return
*   true - if connected
*   false - if not connected
*
*/

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


/**
* Generate random graph for measuring perfomance
*
*  This function takes in the adjacency list and number of vertices and 
*  density and generates a random graph and populates the adjacency list
*
* @param G
*   Adjacency list as unordered_map<int, unordered_map<int,int>>&
* @param n
*   number of vertices
* @param d
*   density of graph
*
* @return
*  VOID
*
*/
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



/**
*  Calls dijikstra and prints the source to all destination distances
*
*  This function takes in the adjacency list and number of vertices and 
*  number of edges, source node, and type and prints the source to all destination distances
*
* @param G
*   Adjacency list as unordered_map<int, unordered_map<int,int>>&
* @param m
*   number of vertices
* @param n
*   number of edges
* @param src
*   source vertex
* @param type
*   enum - fib or leftist - denotes which data type to use
*
* @return
*  VOID
*
*/
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


/**
*  Loads the given file into adjacency list representation of a graph
*
*  This function takes in the adjacency list and number of vertices and 
*  number of edges, source node, and filename this loads the given file into adjacency list representation of a graph
*
* @param G
*   Adjacency list as unordered_map<int, unordered_map<int,int>>&
* @param m
*   number of vertices
* @param n
*   number of edges
* @param src
*   source vertex
* @param filename
*   string filename - indicating the input file name
*
* @return
*  VOID - graph is populated into G
*
*/
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


/**
*  Main function which runs in -r , -f , -l mode
*
*  -r mode:
* 		generates a random graph (connected)
*		runs dijikstra using Fibonacci and measures time
* 		runs dijikstra using leftist tree and measures time
* 		prints time for further comparison
*		
*		$dijikstra -r n d x
*
*	-l mode:
*		loads the graph from the given file and runs dijikstra using leftist tree
*		prints source to all destinations distances
*   
*		$dijikstra -l file-name // read the input from a file ‘file-name’ for leftist tree scheme

*	-f mode:
*		loads the graph from the given file and runs dijikstra using Fibonacci heap
*		prints source to all destinations distances
*
*		$dijikstra -f file-name // read the input from a file ‘file-name’ for Fibonacci heap scheme
*/
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