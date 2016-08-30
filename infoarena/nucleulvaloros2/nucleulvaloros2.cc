#include <fstream>
#include <vector>

using namespace std;

ifstream fin("nucleulvaloros2.in");
ofstream fout("nucleulvaloros2.out");

int main() {
    int n; 
    fin >> n;
    vector<int> el(n, 0);
    for (int i = 0; i < n; i += 1) {
        fin >> el[i];
    }
    
}
