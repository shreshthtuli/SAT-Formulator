#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    ifstream input(argv[1]); // sat output
    ifstream inputG(argv[2]); // graph file
	ofstream output;
	output.open(argv[3]); // results file

    string sat;
    input >> sat;

    // Return if unsatisfiable
    if(sat == "UNSAT"){
        output << 0;
        return 0;
    }

    int nodes, k;
    inputG >> nodes >> k >> k;
    vector<int> *sets = new vector<int>[k];

    // If satisfiable add to vectors
    int num;
    input >> num;

    int node, group;
    while(num != 0){
        if(num > 0){ // add to vector
            node = (num-1) / k;
            group = (num-1) % k;
            sets[group].push_back(node);
        }
        input >> num;
    }

    // If no subset write answer to file
    int size;
    for(int i = 0; i < k; i++){
        size = sets[i].size();
        output << "#" << (i+1) << " " << size << endl;
        for(int j = 0; j < size; j++){
            output << sets[i].at(j)+1 << " ";
        }
        output << endl;
    }

    return 0;
}