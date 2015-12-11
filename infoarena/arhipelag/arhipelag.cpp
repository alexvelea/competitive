#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("arhipelag.in");
ofstream out("arhipelag.out");

const int kMaxN = 100005;

vector<int> rez;
vector<int> vertex[kMaxN];
int R[kMaxN];

bool viz[kMaxN];
int ord[kMaxN], Ord[kMaxN];

int df(int nod) {
	viz[nod] = true;
	int rez = 1;
	for (int itr : vertex[nod])
		if (not viz[itr])
			rez += df(itr);
	return rez;
}

int main() {
	int T;
	in >> T;
	for (int t = 1; t <= T; ++t) {
		int n, m, k;
		in >> n >> m >> k;
		for (int i = 1; i <= n; ++i)
			vertex[i].clear();
		while (m--) {
			int a, b;
        	in >> a >> b;
			vertex[a].push_back(b);
			vertex[b].push_back(a);
		}
		for (int i = 1; i <= n; ++i)
			viz[i] = false;

		rez.clear();

		for (int i = 1; i <= n; ++i)
			if (not viz[i]) {
				rez.push_back(df(i));
			}

		for (int i = 1; i <= k; ++i) {
			in >> ord[i];
			Ord[ord[i]] = i;
		}

		sort(rez.begin(), rez.end());
		reverse(rez.begin(), rez.end());
		int st = 1;
		for (int itr : rez) {
			R[st] += itr;
			++st;
			if (st == k + 1)
				st = 1;
		}
		out << "Case " << t << ": ";
		for (int i = 1; i <= k; ++i)
			out << R[Ord[i]] << ' ';
		out << '\n';
		for (int i = 1; i <= k; ++i)
			R[i] = 0;
	}
    return 0;
}
