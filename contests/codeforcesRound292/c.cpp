//Problem C from Codeforces Round 292
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 200005;

int H[kMaxN];
int64 D[kMaxN];

struct AintNode {
	int64 left, right, best;
	AintNode() {
		left = right = best = -1LL * inf * inf;
	}
	AintNode(AintNode &lft, AintNode &rght) {
		best = max(lft.best, rght.best);
		best = max(best, lft.left + rght.right);

		left = max(lft.left, rght.left);

		right = max(lft.right, rght.right);
	}
	AintNode(int ind) {
		best = -1LL * inf * inf;
		left = H[ind] - D[ind];
		right = H[ind] + D[ind];
	}
} aint[4 * kMaxN];

void makeAint(int nod, int st, int dr) {
	if (st == dr) {
		aint[nod] = AintNode(st);
	} else {
		int m = (st + dr) / 2;
		makeAint(2 * nod, st, m);
		makeAint(2 * nod + 1, m + 1, dr);
		aint[nod] = AintNode(aint[2 * nod], aint[2 * nod + 1]);
	}
}

AintNode aintQuery(int nod, int st, int dr, int c1, int c2) {
	if (dr < c1 or c2 < st) {
		return AintNode();
	}

	if (c1 <= st and dr <= c2) {
//		AintNode rez = aint[nod];
// 	cerr << st << '\t' << dr << '\t' << rez.best << '\t' << rez.left << '\t' << rez.right << '\n';   	
		return aint[nod];
	}

	AintNode r, l;
	int m = (st + dr) / 2;
	l = aintQuery(2 * nod, st, m, c1, c2);;
	r = aintQuery(2 * nod + 1, m + 1, dr, c1, c2);
	AintNode rez = AintNode(l, r);
//	cerr << st << '\t' << dr << '\t' << rez.best << '\t' << rez.left << '\t' << rez.right << '\n';
	return rez;
}

int main() {
	int n, m;
    ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 2; i <= n + 1; ++i) {
		cin >> D[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> H[i];
		H[i] *= 2;
	}
	for (int i = 1; i <= n; ++i) {
		H[i + n] = H[i];
	}
	for (int i = 2; i <= n + 1; ++i) {
		D[i + n] = D[i];
	}

	for (int i = 1; i <= 2 * n; ++i) {
		D[i] += D[i - 1];
	}

	makeAint(1, 1, 2 * n);
	for (int i = 1; i <= m; ++i) {
		int st, dr;
		cin >> st >> dr;
		if (st <= dr) {
			st += n;
			dr++;
			st--;
			swap(st, dr);
		} else {
			st--;
			dr++;
			swap(st, dr);
		}
//		cerr << st << '\t' << dr << "!!!!\n";
		cout << aintQuery(1, 1, 2 * n, st, dr).best << '\n';
	}

	return 0;
}
