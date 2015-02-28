//Problem C from Codeforces Round 290
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

const int inf = 0x3f3f3f3f, source = 201, sink = 202;
int maxFlow = 0;

int father[205], bfs[205], flow[205][205], el[205];

bool getFlow() {
	for (int i = 1; i <= 202; ++i)
		father[i] = 0;
	bfs[0] = source;
	int st = 0, dr = 0;
	while (st <= dr) {
		int nod = bfs[st++];

		for (int i = 1; i <= 202; ++i) {
			if (flow[nod][i] and not father[i]) {
				father[i] = nod;
				bfs[++dr] = i;
			}
		}
	}
	if (father[sink])
		;
	else
		return false;
	for (int nod = sink; nod != source; nod = father[nod]) {
		flow[father[nod]][nod]--;
		flow[nod][father[nod]]++;
	}
	++maxFlow;
	return true;
}

bool prim(int el) {
	for (int d = 2; d * d <= el; ++d) {
		if (el % d == 0)
			return false;
	}
	return true;
}

int viz[205];
vector<int> comp[205];
int nrc;

void df(int nod, int nrc) {
	viz[nod] = true;
	comp[nrc].push_back(nod);
	for (int i = 1; i <= 200; ++i) {
		if (el[nod] % 2 == 0 and el[i] % 2 == 1 and viz[i] == false and flow[i][nod] == 1)
			df(i, nrc);
 		if (el[nod] % 2 == 1 and el[i] % 2 == 0 and viz[i] == false and flow[nod][i] == 1)   		
			df(i, nrc);
	}
}

int main() {
	int n;
    cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];	
	}
	for (int i = 1; i <= n; ++i) {
		if (el[i] % 2 == 0)
			flow[source][i] = 2;
		else
			flow[i][sink] = 2;
	}
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (prim(el[i] + el[j]) and el[i] % 2 == 0) {
				flow[i][j] = 1;
			}
		}
	while (getFlow())
		;
	if (maxFlow == n) {
		for (int i = 1; i <= n; ++i) {
			if (not viz[i]) {
				df(i, nrc);
				nrc++;
			}
		}
		cout << nrc << '\n';
		for (int i = 0; i < nrc; ++i, cout << '\n') {
			cout << comp[i].size() << ' ';
			for (auto itr : comp[i])
				cout << itr << ' ';
		}
	} else {
		cout << "Impossible";
	}
	return 0;
}
