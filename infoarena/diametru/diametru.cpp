//Problem diametru @ 27-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

ifstream fin("diametru.in");
ofstream fout("diametru.out");

int main() {
	int n = 491;
    fout << n + 2 << '\t' << 1225 << '\n';
    // 2 * n - 6 + 4
    int x = 0;
    for (int i = 1; i <= n - 2; ++i) {
        fout << i << ' ' << n + 1 << '\n';
        fout << i << ' ' << n + 2 << '\n';
        x += 2;
    }
    fout << n - 1 << ' ' << n + 1 << '\n'; ++x;
    fout << n << ' ' << n + 2 << '\n'; ++x;
    fout << n + 1 << ' ' << n + 2 << '\n'; ++x;
    for (int i = 5; i <= n; i += 2) {
        fout << 1 << ' ' << i << '\n';
        ++x;
    }
    cerr << x << '\n';
    return 0;
}
