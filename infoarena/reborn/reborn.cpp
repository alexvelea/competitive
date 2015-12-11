//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("reborn.in");
ofstream out("reborn.out");

const int inf = 0x3f3f3f3f, kMaxN = 200005, kMaxQ = 200005;

vector<pair<int, int> > Q[kMaxQ];
vector<int> vertex[kMaxN];
int rez[kMaxQ];
int St[kMaxN];

bool viz[kMaxN];
int df_st[kMaxN], nr_df;


void df(int nod) {
	viz[nod] = true;
	df_st[++nr_df] = nod;
	/* solve query */
	for (pair<int, int> itr : Q[nod]) {
		int oth = itr.first;

        if (df_st[1] > oth)
			continue;

        int r = 0, p = 0;
		while ((1 << p) <= nr_df)
			++p;
		
		for (; p >= 0; --p) {
			if (r + (1 << p) <= nr_df and df_st[r + (1 << p)] <= oth)
				r += (1 << p);
		}
		rez[itr.second] = nr_df - r;
	}

	for (int itr : vertex[nod]) {
		if (not viz[itr]) 
			df(itr);
	}

	--nr_df;
}

int main() {
	int n, m, q;
	in >> n >> m >> q;

    for (int i = 1; i <= n; ++i)
		St[i] = inf;

	for (int i = 1; i <= m; ++i) {
		int st, dr;
		in >> st >> dr;
		St[dr] = min(St[dr], st);
	}

	for (int i = n - 1; i; --i)
		St[i] = min(St[i], St[i + 1]);

//	for (int i = 1; i <= n; ++i)
//		cerr << i << '\t' << St[i] << '\n';

	for (int i = 1; i <= n; ++i) {
		if (St[i] < i)
			vertex[St[i]].push_back(i);
	}
 	
	for (int i = 1; i <= q; ++i) {
		int st, dr;
		in >> st >> dr;
		if (st > dr)
			swap(st, dr);
		
		if (st == dr)
			continue;
		
		Q[dr].push_back(make_pair(st, i));
		rez[i] = -1;
	}
	in.close();

	for (int i = 1; i <= n; ++i)
		if (not viz[i])
			df(i);
	
	for (int i = 1; i <= q; ++i)
		out << rez[i] << '\n';
	out.close();
    return 0;
}
