#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]){
    ifstream input(argv[1]);
	ofstream output;
    output.open(argv[2]);

    int nodes, edges, k, start, end;
    int num_clauses;
    // optimization : num_clauses can be calculated directly

    input >> nodes >> edges >> k;
    ostringstream ss;

    int **matrix = new int*[nodes];
    for(int i = 0; i < nodes; ++i)
        matrix[i] = new int[nodes]{0};
    
    for(int i = 0; i < edges; i++){
        input >> start >> end;
        matrix[start-1][end-1] = 1;
        matrix[end-1][start-1] = 1;
    }

    int terms = k * (nodes *k + edges);
    num_clauses = nodes + (3 * edges * k) + ((nodes*(nodes-1))/2 - edges) * k + k + edges + k * (k - 1) * (3 * nodes + 1); 
    output << "p cnf " << terms << " " << num_clauses << endl;

    int temp, a, b;
    int term = 1;
    // Every node belongs to atleast 1 group
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < k; j++){
            ss << term++ << " ";
        }
        ss << "0\n";
    }

    // ss << "Part 1 complete\n";

    temp = term;
    for(int i = 0; i < nodes; i++){
        for(int j = i+1; j < nodes; j ++){
            a = 1 + k*i;
            b = 1 + k*j;
            if(matrix[i][j] == 1){
                // Neighbors should have atleast one common group
                for(int x = 1; x <= k; x++){
                    ss << -a << " " << -b << " " << term << " 0\n"
                       << a << " " << -term << " 0\n"
                       << b << " " << -term << " 0\n";
                    term++; a++; b++; 
                }
                for(; temp < term; temp++){
                    ss << temp << " ";
                }
                ss << "0\n";
            }
            else{
                // Those that are not neighbors should not have any common group
                for(int x = 1; x <= k; x++){
                    ss << -a << " " << -b << " 0\n";
                    a++; b++; 
                }
            }
        }
    }

    // Atleast 1 in each group
    for(int i = 1; i <= k; i++){
        for(int j = 0; j < nodes; j++){
            ss << k*j + i << " ";
        }
        ss << "0\n";
    }

    // Subgraph check
    for(int i = 1; i < k+1; i++){
        for(int j = 1; j < k+1; j++){
            if(i == j)
                continue;
            a = i; b = j;
            for(int x = 0; x < nodes; x++){
                ss << -a << " " << b << " " << term << " 0\n" 
                   << a << " " << -term << " 0\n" 
                   << -b << " " << -term << " 0\n";
                term++; 
                a+=k; b+=k;
            }
            for(; temp < term; temp++){
                ss << temp << " ";
            }
            ss << "0\n";
            // num_clauses++;
        }
    }

    output << ss.str();
    output.flush();
    output.close();
    return 0;
}