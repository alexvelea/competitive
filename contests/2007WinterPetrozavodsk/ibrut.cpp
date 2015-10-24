#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ifstream fin("transform.in");
    int n; fin >> n;
    vector<int> e;
    for (int i = 1; i <= n; ++i) {
        int x; fin >> x; e.push(x); 
    }
    bt(0, e);
}
