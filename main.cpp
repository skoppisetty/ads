#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iostream>
#include <queue>

using namespace std;
#include "dijikstra.h"


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

int main(int argc, char *argv[]){
	cout << argv[1] << endl;
	unordered_map<int, unordered_map<int,int>> G;
	int src,m,n;
	
	if(string(argv[1]) == "-r"){
		cout << "random" << endl;
		int n = atoi(argv[2]);
		double d = atoi(argv[3]);
		int src = atoi(argv[4]);
		int num_edges = ceil((d * n * (n-1))/200);
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

				// check for edge 
				unordered_map<int,int>::const_iterator got = G[s].find (d);
				if(got == G[s].end()){
					cout << "added edge "<< s << " " << d << endl;
					G[s][d]=ecost;
					G[d][s]=ecost;
					num++;

				}

			}
		}while(is_connected(G,n));
		m = n;
		n = num_edges;
	}
	else  {
		string filename=argv[2]; 
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
		type method;
		vector<int> spath;

		if(argv[1] == "-f")
			method = fib;
		else method = leftist;

		for(int i = 0; i < m ; i++){
			int sval = 0;
			spath = dijikstra(G,src,i,method);  // Run dijkstra to find shortest path
			
			// traverse through shortest path to find path weight
			// cout << "source :"<< src << " Dest: " << i << "		";
			if(spath.empty()){
				cout << "0" << endl;
				continue;
			}
			for(int i=0;i< spath.size()-1;i++){ 
				int s=spath[i];
				int d=spath[i+1];
				sval += G[s][d];
			}

			cout << sval << endl;   // Print the path weight

			// for(int i=0; i < spath.size(); i++){ // print the path
			// 	cout << spath[i] << " "; 
			// }

		}

	return 0;
}
