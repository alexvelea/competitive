#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ofstream fout("buffer");
    for (long long i = 0; i < 1LL * 100 * (1 << 20); ++i) {
        if (i % 100000000 == 0) {
            cerr << 1.0 * i / 1000000000 / 1000 << '\n';
        }
        fout << 'a';
    }
}
