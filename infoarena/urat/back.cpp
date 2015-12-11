#include <iostream>
using namespace std;

int el[25], viz[25], rez, mx;

void bt(int ind, int n) {
	if (ind == n + 1) {
		int act = 0;
		for (int i = 1; i < n; ++i)
			act += abs(el[i] - el[i + 1]);
		if (act > mx) {
			mx = act;
			rez = 0;
		}
		if (act == mx)
			++rez;
		return ;
	}
	for (int i = 1; i <= n; ++i) {
		if (not viz[i]) {
			viz[i] = true;
			el[ind] = i;
			bt(ind + 1, n);
			viz[i] = false;
		}
	}
}

int main() {
	int n = 15;
	for (int i = 2; i <= n; ++i) {
		rez = 0;
		mx = 0;
		bt(1, i);
		cerr << i << '\t' << mx << '\t' << rez << '\n';
	}
}
