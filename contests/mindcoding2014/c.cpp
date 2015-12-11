//Problem #C from Codeforces mindcode
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 1005;

int a[kMaxN], b[kMaxN];
vector<int> uniq, vertex[kMaxN];

int n, m;
int st[kMaxN];
int dr[kMaxN * kMaxN];
bool viz[kMaxN];

int nr_c;

bool cuplaj(int nod) {
	if (viz[nod])
		return false;
	viz[nod] = true;
	for (int itr : vertex[nod]) {
		if (not dr[itr]) {
			dr[itr] = nod;
			++nr_c;
			st[nod] = itr;
			return true;
		}
	}
	for (int itr : vertex[nod]) {
		if (cuplaj(dr[itr])) {
			++nr_c;
			dr[itr] = nod;
			st[nod] = itr;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int j = 1; j <= m; ++j)
		cin >> b[j];
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j) {
			uniq.push_back(a[i] - b[j]);
		}
	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
	for (int i = 1; i <= n; ++i) 
		for (int j = 0; j <= m; ++j) {
			int x = lower_bound(uniq.begin(), uniq.end(), a[i] - b[j]) - uniq.begin() + 1;
			vertex[i].push_back(x);
		}
	
	bool ok = true;
	while (ok) {
		ok = false;
		for (int i = 1; i <= n; ++i)
			if (not st[i] && not viz[i])
				if (cuplaj(i))
					ok = true;
		for (int i = 1; i <= n; ++i)
			viz[i] = false;
	}

	cout << nr_c << '\n';
	for (int i = 1; i <= n; ++i) {
		if (st[i] == 0) 
			cout << a[i] << ' ';
		else
			cout << uniq[st[i] - 1] << ' ';
	}
	cout << '\n';
    return 0;
}

