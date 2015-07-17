#ifndef DIJIKSTRA_H
#define DIJIKSTRA_H

#include <unordered_map>
#include <vector>
#include <climits>
#include <algorithm>
#include "Fibonacci.h"
#include "leftist.h"
using namespace std;

enum type { fib , leftist};

vector<int> dijikstra(unordered_map<int, unordered_map<int,int>>&, int, int, type);

#endif