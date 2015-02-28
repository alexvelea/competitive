//Problem disconnect from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("lca.in");
ofstream out("lca.out");

int n, m;

bool viz[kMaxN];
int deep[kMaxN];

int rmq[kMaxN * 3][20], euler[3 * kMaxN], aib[3 * kMaxN];
int st[kMaxN], dr[kMaxN];

vector<int> vertex[kMaxN];

void df(int nod) {
	euler[++euler[0]] = nod;
	st[nod] = euler[0];
	viz[nod] = true;

	for (int itr : vertex[nod]) {
		if (not viz[itr]) {
			deep[itr] = deep[nod] + 1;
			df(itr);
		 	euler[++euler[0]] = nod;   		
		}
	}
 	euler[++euler[0]] = nod;
	dr[nod] = euler[0];
 	return ;
}

int lca(int a, int b) {
	a = st[a];
	b = st[b];
	if (a > b)
		swap(a, b);
	if (a == b)
		return euler[a];
	
	int p = 0;
	while (b - a + 1 > (1 << (p + 1)))
		++p;
	b -= (1 << p) - 1;
	if (deep[rmq[a][p]] < deep[rmq[b][p]])
		return rmq[a][p];
	else
		return rmq[b][p];
}

int main() {
	in >> n >> m;
	for (int i = 2; i <= n; ++i) {
		int a, b;
		in >> b;
		a = i;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	df(1);
	for (int i = 1; i <= euler[0]; ++i)
		rmq[i][0] = euler[i];
	for (int p = 1; (1 << p) <= euler[0]; ++p) {
		for (int i = 1; i + (1 << p) - 1 <= euler[0]; ++i) {
			if (deep[rmq[i][p - 1]] < deep[rmq[i + (1 << (p - 1))][p - 1]])
				rmq[i][p] = rmq[i][p - 1];
			else
				rmq[i][p] = rmq[i + (1 << (p - 1))][p - 1];
		}
	}

	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		out << lca(a, b) << '\n';
	}
	return 0;
}
