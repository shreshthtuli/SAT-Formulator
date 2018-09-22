#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
private:
    int num_nodes;
    int num_edges;
    vector<int> *adjList;

public:
    Graph(int num_nodes, int num_edges);
    void addEdge(int u, int v);
    bool areAdj(int u, int v);

};

#endif  /* GRAPH_H */