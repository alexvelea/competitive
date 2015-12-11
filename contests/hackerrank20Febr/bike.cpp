#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

const int kMaxN = 255;

vector<int> vertex[kMaxN];
bool viz[kMaxN];
int pairA[kMaxN], pairB[kMaxN];
int n, m, k;
int x[kMaxN], y[kMaxN];
int xB[kMaxN], yB[kMaxN];

int64 dist(int a, int b) {
	return 1LL * (x[a] - xB[b]) * (x[a] - xB[b]) + 1LL * (y[a] - yB[b]) * (y[a] - yB[b]);
}

bool findAugPath(int nod) {
	viz[nod] = true;
	for (int itr : vertex[nod])
		if (not pairB[itr]) {
			pairA[nod] = itr;
			pairB[itr] = nod;
			return true;
		}
	for (int itr : vertex[nod])
		if (not viz[pairB[itr]] and findAugPath(pairB[itr])) {
        	pairA[nod] = itr;
			pairB[itr] = nod;
			return true;
		}
	return false;
}

bool solve(int64 D) {
	for (int i = 1; i <= n; ++i) {
		vertex[i].clear();
		pairA[i] = 0;
	}
	for (int i = 1; i <= m; ++i)
		pairB[i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (dist(i, j) <= D)
				vertex[i].push_back(j);
	int nrMatched = 0;
	while (true) {
		bool ok = false;
		for (int i = 1; i <= n; ++i)
			viz[i] = false;
		for (int i = 1; i <= n; ++i)
			if (viz[i] == false and pairA[i] == 0 and findAugPath(i)) {
 	   			ok = true;
				++nrMatched;
			}
		if (nrMatched >= k)
			return true;
		if (not ok)
			return false;
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		cin >> x[i] >> y[i];
	for (int i = 1; i <= m; ++i)
		cin >> xB[i] >> yB[i];
	int64 p = (1LL << (24 + 2));
	int64 rez = 0;
	for (; p; p >>= 1LL)
		if (solve(p + rez))
			;
		else
			rez += p;
	if (solve(0))
		cout << "0\n";
	else
		cout << rez + 1LL << '\n';
	return 0;
}
