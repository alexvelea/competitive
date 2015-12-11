#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int max_n = 5000005;
ifstream in("otilia.in");
ofstream out("otilia.out");

struct trio {
	int n, k, i;
	trio () {
		n = k = i = 0;
	}
	trio (int _n, int _k, int _i) {
		n = _n;
		k = _k;
		i = _i;
	}
};

pair<int,int> st[max_n];
int ind;

vector<trio> Q[11];
int rez[35000];
int Best[max_n];
int mx[11];

int main() {
	int m = 0;
	in >> m;
	for (int i = 1; i <= m; ++i) {
		int n, k, p;
		in >> n >> k >> p;
		Q[p].push_back(trio(n, k, i));
		mx[p] = max(mx[p], n);
	}
	Best[0] = Best[1] = max_n + 5;
	st[1] = make_pair(1, 2*max_n + 5);
	for (int p = 1; p <= 10; ++p) {
		ind = 1;
		for (int i = 2; i < max_n; ++i) {
			while (st[ind].second < i)
				--ind;
			Best[i] = i - st[ind].first;
			int dr = (Best[i] - 1) / p + i;
			while (st[ind].second <= dr)
		    	--ind;
			st[++ind] = make_pair(i, dr);
		}
		for (int i = 0; i < int(Q[p].size()); ++i)
			rez[Q[p][i].i] = (Q[p][i].k >= Best[Q[p][i].n]);
	}
	for (int i = 1; i <= m; ++i)
		out << rez[i] << '\n';
	return 0;
}
