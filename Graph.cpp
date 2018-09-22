#include "Graph.h"

Graph::Graph(int num_nodes, int num_edges)
{
    this->adjList = new vector<int>[num_nodes];
    this->num_nodes = num_nodes;
    this->num_edges = num_edges;
}

void Graph::addEdge(int u, int v)
{
    this->adjList[u].push_back(v);
    this->adjList[v].push_back(u);
}

bool Graph::areAdj(int u, int v)
{
    // optimization
    int size, a, b;
    if(this->adjList[u].size() < this->adjList[v].size()){
        size = this->adjList[u].size();
        a = u;
        b = v;
    }
    else{
        size = this->adjList[v].size();
        a = v;
        b = u;
    }

    for(int i = 0; i < size; i++){
        if(this->adjList[a].at(i) == b)
            return true;
    }

    return false;
}