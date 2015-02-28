#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("spargere2.in");
ofstream out("spargere2.out");

const int kMaxN = 100005;

int el[kMaxN];
int64 best[kMaxN];

int main() {
	int n, k;
	in >> n >> k;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	for (int i = 1; i <= n; ++i) {
		if (i > k)
			best[i] = best[i - k] + el[i];
		else
			best[i] = el[i];
		best[i] = max(best[i - 1], best[i]);
	}
	out << best[n] << '\n';
    return 0;
}
