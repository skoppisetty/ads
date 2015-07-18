/**
 * This is Dijikstra's implementation. 
 *
 **/
#include <iostream>
#include "dijikstra.h"
using namespace std;


/**
 * Implements dijikstras algorithm 
 *
 * @param G
 *   Graph represented as an adjacency list 
 * @param src
 *   source node value
 * @param des
 *	 destination node value
 * @param Type 
 *   Underlying data structure used(fib heap/leftist tree)
 *
 * @return
 *   vector of distances of each node from source node
 **/
vector<int> dijikstra(unordered_map<int, unordered_map<int,int>> &G, int src, int des, type Type){
	int* dist = new int[G.size()];
	int* prev = new int[G.size()];
	if(Type == leftist){
		unordered_map<int,LeftistNode*> addr;
		LeftistHeap fh;
			vector<int> path;
	if(src == des){
		return path;
	}
	int count=0;
	for(int i=0;i<G.size();i++){
		if(i==src){
			dist[i]=0;
			addr[i]=fh.Insert(i,0);
		} else {
			dist[i]=INT_MAX;
			addr[i]=fh.Insert(i,INT_MAX);
		}
		count++;
	} 
	while(!fh.empty()){
		LeftistNode *n = fh.RemoveMin();
		if(n->vertex == des){
			int temp=des;
			while(prev[temp]!=src){
				path.insert(path.begin(),temp);
				temp=prev[temp];
			}
			path.insert(path.begin(),temp);
			path.insert(path.begin(),src);
			break;
		}
		for(auto i : G[n->vertex]){ 
			int newdist = dist[n->vertex] + i.second;
			// cout << dist[n->vertex] << endl;
			// cout << i.first << " " <<  i.second << endl;
			// cout << "vertex: " << n->vertex << endl;
			// cout << "dist: " << newdist << endl;
			// cout << "dist first " << dist[i.first] << endl;
			if(newdist < dist[i.first]){
				addr[i.first] = fh.DecreaseKey(addr[i.first],newdist);
				dist[i.first] = newdist;
				prev[i.first] = n->vertex;
			}
		}
	}
	//cout << endl;
	return path;
	}
	else{
		unordered_map<int,node*> addr;
		Fibonacci_heap fh;
			vector<int> path;
	if(src == des){
		return path;
	}
	int count=0;
	for(int i=0;i<G.size();i++){
		if(i==src){
			dist[i]=0;
			addr[i]=fh.Insert(i,0);
		} else {
			dist[i]=INT_MAX;
			addr[i]=fh.Insert(i,INT_MAX);
		}
		count++;
	} 
	while(!fh.empty()){
		node *n = fh.RemoveMin();
		if(n->vertex == des){
			int temp=des;
			while(prev[temp]!=src){
				path.insert(path.begin(),temp);
				temp=prev[temp];
			}
			path.insert(path.begin(),temp);
			path.insert(path.begin(),src);
			break;
		}
		for(auto i : G[n->vertex]){ 
			int newdist = dist[n->vertex] + i.second;
			// cout << dist[n->vertex] << endl;
			// cout << i.first << " " <<  i.second << endl;
			// cout << "vertex: " << n->vertex << endl;
			// cout << "dist: " << newdist << endl;
			// cout << "dist first " << dist[i.first] << endl;
			if(newdist < dist[i.first]){
				fh.DecreaseKey(addr[i.first],newdist);
				dist[i.first]=newdist;
				prev[i.first]=n->vertex;
			}
		}
	}
	//cout << endl;
	return path;
	}
}


