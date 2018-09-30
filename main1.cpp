#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[]){
    ifstream input(argv[1]);
	ofstream output;
    output.open(argv[2]);

    int nodes, edges, k, start, end;

    input >> nodes >> edges >> k;

    // 0 edge test case
    if(edges == 0 && k < nodes){
        output << "p cnf 1 2\n1 0\n-1 0\n";
        output.flush(); output.close(); return 0;
    }

    ostringstream ss;

    int **matrix = new int*[nodes];
    for(int i = 0; i < nodes; ++i)
        matrix[i] = new int[nodes]{0};
    
    for(int i = 0; i < edges; i++){
        input >> start >> end;
        matrix[start-1][end-1] = 1;
        matrix[end-1][start-1] = 1;
    }

    int terms = k * (nodes * k + edges);
    int temp, a, b, i, j, x;
    int term = k+1;
    vector<int> next;
    bool flag;
    int grp_assigned = 2;
    int num_clauses = 1;

    // Assign first node to group 1
    ss << "1 0\n";
    next.push_back(0);
    for(i = 1; i < nodes; i++){
        flag = true;
        for(j = 0; j < next.size(); j++){
            flag = flag && (matrix[i][next.at(j)] == 0);
        }
        if(flag){
            // Assign next node to next group and not to previous groups
            next.push_back(i);
            ss << i*k + grp_assigned++ << " 0\n";
            for(x = 1; x < grp_assigned-1; x++){
                ss << -(i*k + x) << " 0\n";
            }
            num_clauses += (grp_assigned - 1);
        }
    }

    // grp_assigned > K case
    if(grp_assigned > k){
        output << "p cnf 1 2\n1 0\n-1 0\n";
        output.flush(); output.close(); return 0;
    }

    // Every node belongs to atleast 1 group - check all nodes except assigned
    for(i = 1; i < nodes; i++){
        if(find(next.begin(), next.end(), i) != next.end()){
            term += k;
            continue;
        }
        for(j = 0; j < k; j++){
            ss << term++ << " ";
        }
        ss << "0\n";
        num_clauses++;
    }

    temp = term;
    // Subgraph check
    for(i = 1; i < k+1; i++){
        for(j = 1; j < k+1; j++){
            if(i == j)
                continue;
            a = i; b = j;
            for(x = 0; x < nodes; x++){
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
            num_clauses += (3*nodes + 1);
        }
    }

    for(i = 0; i < nodes; i++){
        for(j = i+1; j < nodes; j ++){
            a = 1 + k*i;
            b = 1 + k*j;
            if(matrix[i][j] != 0){
                // Neighbors should have atleast one common group
                for(x = 1; x <= k; x++){
                    ss << -a << " " << -b << " " << term << " 0\n"
                       << a << " " << -term << " 0\n"
                       << b << " " << -term << " 0\n";
                    term++; a++; b++;
                }
                for(; temp < term; temp++){
                    ss << temp << " ";
                }
                ss << "0\n";
                num_clauses += (3*k + 1);
            }
            else{
                // Those that are not neighbors should not have any common group
                for(x = 1; x <= k; x++){
                    ss << -a << " " << -b << " 0\n";
                    a++; b++; 
                }
                num_clauses += k;
            }
        }
    }

    // Atleast 1 in each group - check except groups 1 to grp_assigned
    for(i = grp_assigned; i <= k; i++){
        for(j = 0; j < nodes; j++){
            ss << k*j + i << " ";
        }
        ss << "0\n";
        num_clauses++;
    }

    output << "p cnf " << terms << " " << num_clauses << endl;
    output << ss.str();
    output.flush();
    output.close();
    return 0;
}