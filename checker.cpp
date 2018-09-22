#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    ifstream input(argv[1]);

    int num_vars;
    cout << "Checking file\n";
    string s;
    input >> s >> s >> s;
    num_vars = stoi(s);
    cout << "Num vars : " << num_vars << endl;
    int num_clauses;
    input >> num_clauses;
    cout << "Num clauses : " << num_clauses << endl;
    int *a = new int[num_vars]();
    a[0] = 1;
    a[1] = 1;
    a[2] = 0;
    a[3] = 1;
    a[4] = 1;
    a[5] = 0;
    a[6] = 0;
    a[7] = 1;
    a[8] = 1;
    a[9] = 1;
    a[10] = 0;
    a[11] = 1;
    a[12] = 0;
    a[13] = 0;
    a[14] = 1;
    int num;
    input >> s;
    num = stoi(s);
    cout << "Num : " << num << endl;

    for(int i = 0; i < num_clauses; i++){
        bool t1 = false;
        // cout << "Checking line : " << i << endl;
        while(num != 0){          
            t1 = t1 || ((num > 0 && a[abs(num)-1] == 1) || (num < 0 && a[abs(num)-1] == 0));
            input >> s;
            num = stoi(s);
        }
        if(t1 == false)
            cout << "Problem at line : " << i+2 << endl;
        input >> s;
        num = stoi(s);
    }

    return 0;
}