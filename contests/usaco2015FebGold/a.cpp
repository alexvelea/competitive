//Problem A from Codeforces Round usaco2015FebGold
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

ifstream in("hopscotch.in");
ofstream out("hopscotch.out");

const int inf = 0x3f3f3f3f, kMaxN = 755, kMod = 1000000007;

vector<int> aib[kMaxN * kMaxN], col[kMaxN * kMaxN];
int el[kMaxN][kMaxN];

int untilHere[kMaxN][kMaxN];

void Mod(int &a) {
	if (a >= kMod)
		a -= kMod;
	if (a < 0)
		a += kMod;
}

int aibQuery(int ind, int itr) {
	int rez = 0;
	while (itr) {
		rez += aib[ind][itr]; Mod(rez);
		itr -= itr & (-itr);
	}
	return rez;
}

void aibUpdate(int ind, int itr, int val) {
	while (itr < int(aib[ind].size())) {
		aib[ind][itr] += val; Mod(aib[ind][itr]);
		itr += itr & (-itr);
	}
	return ;
}

int main() {
	int n, m, k;
    in >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			in >> el[i][j];
		}
	}
	
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) {
			col[el[i][j]].push_back(j);		
		}
	}
	
	for (int i = 1; i <= k; ++i) {
		col[i].resize(unique(col[i].begin(), col[i].end()) - col[i].begin());
	}

 	for (int i = 1; i <= k; ++i) {
		aib[i].resize(col[i].size() + 1);
	}
	untilHere[1][1] = 1;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int itr = lower_bound(col[el[i][j]].begin(), col[el[i][j]].end(), j) - col[el[i][j]].begin();
			untilHere[i][j] += untilHere[i - 1][j - 1] - aibQuery(el[i][j], itr);
			Mod(untilHere[i][j]);
		}
		for (int j = 1; j <= m and i != m; ++j) {
			aibUpdate(el[i][j], lower_bound(col[el[i][j]].begin(), col[el[i][j]].end(), j) - col[el[i][j]].begin() + 1, untilHere[i][j]);
			untilHere[i][j] += untilHere[i][j - 1]; Mod(untilHere[i][j]);
			untilHere[i][j] += untilHere[i - 1][j]; Mod(untilHere[i][j]);
			untilHere[i][j] -= untilHere[i - 1][j - 1]; Mod(untilHere[i][j]);
		}
	}
	
	out << untilHere[n][m] << '\n';
	return 0;
}
