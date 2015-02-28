// Problem D from Codeforces Round rockethon2015
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
vector<int> vertex[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod])
		if (not viz[itr])
			df(itr);
	topo[++topo[0]] = nod;
}

void solve(int st, int dr) {
//	cerr << st << '\t' << dr << '\n';
	while (st <= dr and topo[st] % 4) {
		++st;
	}
	if (st > dr)
		return ;
	int nod = topo[st];
//	cerr << st << '\t' << dr << '\t' << nod << '\t' << where[nod] << '\t' << where[nod + 1]  << '\t' << where[nod + 2] << '\n';
//	cerr << "\n\n";
	assert(where[nod + 1] <= dr);
	assert(where[nod + 2] <= dr);
	solve(st + 1, where[nod + 2] - 1);
	cout << nod / 4 << ' ';
	solve(where[nod + 2], dr);
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	int n, c;
    cin >> n >> c;
	for (int i = 1; i <= n; ++i) {
		if (i != n) 
		vertex[i * 4 + 1].push_back((i + 1) * 4);
		vertex[i * 4].push_back(i * 4 + 1);
		vertex[i * 4 + 1].push_back(i * 4 + 2);
		vertex[i * 4 + 2].push_back(i * 4 - 1);
	}
	for (int i = 1; i <= c; ++i) {
		string LR;
		int a, b;
		cin >> a >> b >> LR;
		a *= 4;
		b *= 4;
		if (LR == "LEFT") {
    		vertex[a + 1].push_back(b);
			vertex[b - 1].push_back(a + 2);
		} else {
			vertex[a + 2].push_back(b);
			vertex[b - 1].push_back(a - 1);
		}

	}
	n *= 4;
	for (int i = 3; i <= n; ++i) {
		if (not viz[i])
			df(i);
	}
	reverse(topo + 1, topo + n + 1);
	for (int i = 1; i <= n; ++i) {
		where[topo[i]] = i;
	}
//	for (int i = 1; i <= n; ++i) {
//		cerr << topo[i] << '\t';
//    }

//	cerr << "\n\n";
	bool ok = true;
	for (int i = 1; i <= n + 4; ++i) {
		for (auto itr : vertex[i]) {
			if (where[itr] < where[i])
				ok = false;
		}
	}
	if (not ok) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	solve(1, n);
	return 0;
}
