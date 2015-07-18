/**
 * This is header file to be used by dijikstras implementation.
 *
 **/

#ifndef DIJIKSTRA_H
#define DIJIKSTRA_H

#include <unordered_map>
#include <vector>
#include <climits>
#include <algorithm>
#include "Fibonacci.h"
#include "leftist.h"
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
enum type { fib , leftist};

vector<int> dijikstra(unordered_map<int, unordered_map<int,int>>&, int, int, type);

#endif