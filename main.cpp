#include <fstream>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[]){
    ifstream input(argv[1]);
	ofstream output;
	output.open(argv[2]);

    int nodes, edges, k, start, end;
    input >> nodes >> edges >> k;
    Graph *g = new Graph(nodes, edges);

    for(int i = 0; i < edges; i++){
        input >> start >> end;
        g->addEdge(start-1, end-1);
    }
}