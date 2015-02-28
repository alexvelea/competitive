#include <cassert>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int kMaxN = 300005;

struct Node {
	int sgv, l, c;
	Node() {
		sgv = l = c = 0;
	}
};
vector<Node> bfs[2];

string A, B, suffix[2][kMaxN];
int sgv[30], total_sgv;

int solve(int ind, int st, int dr, int poz) {
	bfs[ind].push_back(Node());
	int nr = bfs[ind].size() - 1;
	bool viz[27];
	for (int i = 0; i < 27; ++i)
		viz[i] = false;
	while (st < dr and int(suffix[ind][st].size()) == poz)
		++st;
	for (; st < dr; ) {
		int c_st = st;
		while (st < dr and suffix[ind][c_st][poz] == suffix[ind][st][poz])
			++st;
		viz[solve(ind, c_st, st, poz + 1)] = true;
	}
	for (int i = 0; i < 27; ++i)
		if(viz[i] == false) {
			if (ind == 1) {
	        	total_sgv++;
				sgv[i]++;
			} 
			bfs[ind][nr].sgv = i;
			bfs[ind][nr].l = dr - 1;
			bfs[ind][nr].c = poz - 1;
//			cerr << ind << '\t' << i_st << '\t' << dr << '\t' << poz << '\t' << nr << '\n';
			return i;
		}
	assert(0);
}

void show(int ind, int l, int c) {
	for (int i = 0; i <= c; ++i)
		cout << suffix[ind][l][i];
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		char c;
		cin >> c;
		A += c;
	}
	for (int i = 0; i < m; ++i) {
		char c;
		cin >> c;
		B += c;
	}
	assert(n < 3000 and m < 3000);
	for (int i = 0; i < int(A.size()); ++i) 
		for (int j = i; j < int(A.size()); ++j)
			suffix[0][i] += A[j];

 	for (int i = 0; i < int(B.size()); ++i) 
		for (int j = i; j < int(B.size()); ++j)
			suffix[1][i] += B[j];
	

	sort(suffix[0] + 0, suffix[0] + A.size());
	sort(suffix[1] + 0, suffix[1] + B.size());

//	for (int i = 0; i < int(B.size()); ++i)
//		cout << suffix[1][i] << '\n';

	solve(0, 0, int(A.size()), 0);
	solve(1, 0, int(B.size()), 0);
//	for (int i = 0; i < bfs[1].size(); ++i) {
//		show(1, bfs[1][i].l, bfs[1][i].c);
//		cerr << '\t' << bfs[1][i].sgv << '\n';
//	}
	for (int i = 0; k > 0 and i < int(bfs[0].size()); ++i) {
		int x = total_sgv - sgv[bfs[0][i].sgv];
		if (x >= k) {
			show(0, bfs[0][i].l, bfs[0][i].c);
			cout << '\n';
			int val = bfs[0][i].sgv;
			for (int j = 0; k and j < int(bfs[1].size()); ++j) {
				if (bfs[1][j].sgv != val)
					--k;
				if (k == 0)
					show(1, bfs[1][j].l, bfs[1][j].c);
			}
		}
		k -= x;
	}
	return 0;
}
