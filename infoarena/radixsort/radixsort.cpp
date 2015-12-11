#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("radixsort.in");
ofstream out("radixsort.out");

const int kMaxN = 10000005;

int el[kMaxN], n;

void solve(int st, int dr, int p) {
	if (st >= dr)
		return ;
	if (p == -1)
		return ;
	
	int S = st, D = dr;
	while (1) {
 		while (st <= dr and (el[st] & (1 << p)) == 0)
 			++st;
		while (dr >= st and (el[dr] & (1 << p)) != 0)
			--dr;
		if (st <= dr)
			swap(el[st], el[dr]);
		else {
			solve(S, st - 1, p - 1);
			solve(st, D, p - 1);
			return ;
		}
	}
}

int main() {
	int a, b, c;
	in >> n >> a >> b >> c;
	el[1] = b;
	for (int i = 2; i <= n; ++i)
		el[i] = (1LL * a * el[i - 1] + b) % c;

	solve(1, n, 30);
//	for (int i = 1; i <= n; ++i)
//		cout << el[i] << '\t';
	for (int i = 1; i <= n; i += 10)
		out << el[i] << ' ';
    return 0;
}
