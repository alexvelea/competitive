#include <iostream>
#include <fstream>
using namespace std;
int main() {
    int n = 6;
    for (int i = 0; i < (1 << n); i += 1) {
        string s = "";
        for (int j = 0; j < n; j += 1) {
            if ((1 << j) & i) {
                s += "0";
            } else {
                s += "1";
            }
        }
        ofstream fout("penis");
        fout << s << '\n';
        fout.close();
        
        cerr << "#!@#@!#\t" << s << '\n';
        system(string("./_k <penis").c_str());
    }
    return 0;
}
