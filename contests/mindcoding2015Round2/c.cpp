//Problem C from Codeforces Round mindcodingRound2
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

int father[20][kMaxN], deep[kMaxN];
int letter[kMaxN];

vector<int> vertex[kMaxN];

void df(int nod) {
	for (auto itr : vertex[nod]) {
		if (deep[itr] == 0) {
			deep[itr] = deep[nod] + 1;
			father[0][itr] = nod;
			letter[itr] ^= letter[nod];
			df(itr);
		}
	}
	return ;
}

void makeFather(int nod) {
	for (int l = 1; l < 20; ++l) {
   		father[l][nod] = father[l - 1][father[l - 1][nod]];
		if (father[l][nod] == 0)
			return ;
	} 
}

int lca(int a, int b) {
	if (deep[a] < deep[b]) {
		swap(a, b);
	}
	int d = deep[a] - deep[b];

//	cerr << "~~~~\t" << a << '\t' << b << '\n';
	for (int i = 0; d and i < 20; ++i) 
		if (d & (1 << i)) {
			a = father[i][a];
		}
// 	cerr << "~~~~\t" << a << '\t' << b << '\n';
 
	if (a == b)
		return a;

	for (int i = 19; i >= 0; --i) {
		if (father[i][a] != father[i][b]) {
			a = father[i][a];
			b = father[i][b];
		}
	}
	return father[0][a];
}

int main() {
	ios::sync_with_stdio(false);
	int n, m;
    cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		char c; cin >> c;
		letter[i] ^= 1 << (c - 'a');
	}

	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	deep[1] = 1;
	df(1);

	for (int i = 1; i <= n; ++i) {
		makeFather(i);
	}
//	for (int i = 1; i <= 3; ++i, cerr << '\n')
//		for (int j = 0; j < 3; ++j)
//			cerr << father[j][i] << '\t';
//    cerr << father[1][2] << "!!!~~~<-------\n";
	while (m--) {
		int t;
		cin >> t;
		if (t == 2) {
    		// add
			int nod;
			char c;
			cin >> nod >> c;
			
			letter[n + 1] = letter[nod] ^ (1 << (c - 'a'));
			father[0][n + 1] = nod;
			deep[n + 1] = deep[nod] + 1;

			makeFather(n + 1);
			++n;
		} else {
			int x, y;
			cin >> x >> y;
			int lowest = lca(x, y);
//			cerr << x << '\t' << y << '\t' << lowest << "!!!!!!\n";
            int rez = letter[x] ^ letter[y] ^ letter[lowest] ^ letter[father[0][lowest]];
            int rez2 = 0;
			while (rez) {
				rez2++;
				rez -= rez & (-rez);
			}
			cout << rez2 << '\n';
		}
	}
	return 0;
}
