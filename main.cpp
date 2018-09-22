#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[]){
    ifstream input(argv[1]);
	ofstream output;
	output.open(argv[2]);

    int nodes, edges, k, start, end;
    int num_clauses = 0;
    // optimization : num_clauses can be calculated directly

    input >> nodes >> edges >> k;
    stringstream ss;

    int **matrix = new int*[nodes];
    for(int i = 0; i < nodes; ++i)
        matrix[i] = new int[nodes]{0};

    for(int i = 0; i < edges; i++){
        input >> start >> end;
        matrix[start-1][end-1] = 1;
        matrix[end-1][start-1] = 1;
    }

    int term = 1;
    // Every node belongs to atleast 1 group
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < k; j++){
            ss << term++ << " ";
        }
        ss << 0 << endl;
        num_clauses++;
    }

    int bin;
    for(int i = 0; i < nodes; i++){
        for(int j = i+1; j < nodes; j ++){
            if(matrix[i][j] == 1){
                // Neighbors should have atleast one common group
                bin = 1;
                while(bin < (1 << k) - 1){
                    for(int x = 1; x <= k; x++){
                        if((bin & (1<<(k-x))) == 0)
                            ss << (x + k*i) << " ";
                        else    
                            ss << (x + k*j) << " ";
                    }
                    bin++;
                    ss << 0 << endl;
                    num_clauses++;
                }
            }
            else{
                // Those that are not neighbors should not have any common group
                for(int x = 1; x <= k; x++){
                    ss << -(x + k*i) << " " << -(x + k*j) << " " << 0 << endl;
                    num_clauses++;
                }
            }
        }
    }

    // Atleast 1 in each group
    for(int i = 1; i <= k; i++){
        for(int j = 0; j < nodes; j++){
            ss << k*j + i << " ";
        }
        ss << 0 << endl;
        num_clauses++;
    }

    cout << ss.str();
}