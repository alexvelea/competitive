#include <fstream>
using namespace std;
ifstream fin("data.txt");

#include "parsare.cpp"

#define int64 long long

int main() {
    int64 s = 0;
    int n; 
    fin >> n;
//    readNumber(n);
    for (int i = 1; i <= n; ++i) {
        int x; 
        fin >> x;
//        readNumber(x);
        s += x;
    }
    return 0;
}
