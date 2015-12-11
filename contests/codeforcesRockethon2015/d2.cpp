//Problem D from Codeforces Round rockethon2015
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

const int inf = 0x3f3f3f3f, kMaxN = 4 * 1000005;

int topo[kMaxN], where[kMaxN];
bool viz[kMaxN];
vector<int> query[kMaxN][2];

int n;

void df(int nod) {
	if (viz[nod])
		return ;
	viz[nod] = true;
	for (auto itr : query[nod][0])
		df(itr);
	for (auto itr : query[nod][1])
		df(itr);
}

void solve(int nod, int n) {
	for (int i = nod; i <= n; ++i)
		viz[i] = false;
	for (auto itr : query[nod][0])
		df(itr);
	bool ok = true;
	int mx = nod;
	while (ok) {
		for (int  i = nod + 1; i <= n; ++i)
			if (viz[i])
				mx = i;
		ok = false;
		for (int i = nod + 1; i <= mx; ++i)
			if (not viz[i]) {
				df(i);
				ok = true;
			}
	}
	if (mx != nod)
		solve(nod + 1, mx);
	cout << nod << ' ';
	if (mx != n)
		solve(mx + 1, n);
}

int main() {
	ios::sync_with_stdio(false);
    int c;
	cin >> n >> c;
	for (int i = 1; i <= c; ++i) {
		string LR;
		int a, b;
		cin >> a >> b >> LR;
		if (LR == "LEFT") {
			query[a][0].push_back(b);
		} else {
			query[a][1].push_back(b);
		}
	}
	
   	solve(1, n);

	return 0;
}
