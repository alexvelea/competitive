#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("xnumere.in");
ofstream out("xnumere2.out");

const int inf = 0x3f3f3f3f, kMod = 666013;

int el[20], n, k, x;
long long rez;

void bt(int ind) {
	if (ind == n) {
		bool viz[20];
		for (int i = 0; i < k; ++i)
			viz[i] = 1;
		int X = 0;
		for (int i = 0; i < n; ++i) {
			X += viz[el[i]];
			viz[el[i]] = false;
		}
		if (X == x)
			++rez;
		if (rez >= kMod)
			rez -= kMod;
		return ;
	}
	for (int i = 0; i < k; ++i) {
		el[ind] = i;
		bt(ind + 1);
	}
}

int main() {
	in >> k >> x >> n;
	in.close();
	bt(0);
	out << rez << '\n';
	out.close();
    return 0;
}
