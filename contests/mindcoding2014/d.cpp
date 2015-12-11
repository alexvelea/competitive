//Problem #D from Codeforces mindcode
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kSigma = 127, Mod[2] = {666013, 666017}, kMaxN = 100005;

int down[kMaxN][2], up[kMaxN][2];
int sig[2][kMaxN], el[kMaxN];

bool viz[kMaxN];
vector<int> vertex[kMaxN];
int rez;

void df(int nod, int d) {
	viz[nod] = true;
	for (int itr : vertex[nod]) {
		if (viz[itr])
			continue;
		up[itr][0] = ((up[nod][0] * kSigma) + el[itr]) % Mod[0];
		up[itr][1] = ((up[nod][1] * kSigma) + el[itr]) % Mod[1];

		down[itr][0] = (down[nod][0] + sig[0][d] * el[itr]) % Mod[0];
		down[itr][1] = (down[nod][1] + sig[1][d] * el[itr]) % Mod[1];
		df(itr, d + 1);
	}
	if (down[nod][0] == up[nod][0] and down[nod][1] == up[nod][1])
		rez = max(rez, d);
	return ;
}

int e[105], h[105];
string txt;

int main() {
	for (int i = 0; i < 100; ++i)
		e[i] = i + 1;
	random_shuffle(e + 0, e + 100);
	for (int i = 0; i < 26; ++i)
		h[i] = e[i];
	
	sig[0][0] = 1;
	sig[1][0] = 1;
	for (int i = 1; i < kMaxN; ++i) {
		sig[0][i] = (sig[0][i - 1] * kSigma) % Mod[0];
		sig[1][i] = (sig[1][i - 1] * kSigma) % Mod[1];
	}

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cin >> txt;
		for (int i = 0; i < n; ++i)
			el[i + 1] = h[txt[i] - 'a'];

		for (int i = 1; i <= n; ++i)
			vertex[i].clear();

		for (int i = 1; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			vertex[a].push_back(b);
 			vertex[b].push_back(a);
		}
		for (int i = 1; i <= n; ++i)
			viz[i] = false;
		up[1][0] = up[1][1] = down[1][0] = down[1][1] = el[1];
		rez = 0;
		df(1, 1);
		cout << rez << '\n';
	}
    return 0;
}

