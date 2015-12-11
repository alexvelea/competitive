#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define FORIT(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int root = 1, max_n = 100005;

vector<int> vertex[max_n];

vector<int> aib[max_n];
int root_val;

int chain[max_n], chain_length[max_n], vertex_deep[max_n];
bool viz[max_n];


void df_chain (int nod, int ch, int deep);

void reserve_vector (vector<int> &a, int s) {
	for (int i = 0; i < s; ++i) 
		a.push_back(0);
}

void update_aib (int where, int ind, int val) {
	ind = max (1, ind);
	while (ind < int(aib[where].size()) ) {
		aib[where][ind] += val;
		ind += ind & (-ind);
	}
	return ;
}

int query_aib (int where, int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[where][ind];
		ind -= ind & (-ind);
	}
	return rez;
}

int main() {

//	freopen ("text.in", "r", stdin);
//	freopen ("text.out", "w", stdout);

	int n, q;
	cin >> n >> q;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		vertex[a].push_back (b);
		vertex[b].push_back (a);
	}
	viz[1] = 1;
	FORIT (it, vertex[root]) {
		++chain_length[0];
		df_chain (*it, chain_length[0], 1);
	}
 	reserve_vector (aib[0], n+5);
	for (int i = 1; i <= chain_length[0]; ++i)
		reserve_vector (aib[i], chain_length[i]+5);
	for (; q; --q) {
		int t;
		cin >> t;
		if (t == 0) {
			int v, x, d;
			cin >> v >> x >> d;

            if (v == root) {
				root_val += x;
				update_aib (0, 1, x);
				update_aib (0, d+1, -x);
				continue;
			}

 			int l_deep, h_deep;
			l_deep = vertex_deep[v] - d;
			h_deep = vertex_deep[v] + d;
			if (h_deep >= chain_length[chain[v]])
				h_deep = chain_length[chain[v]];
 			int mid_deep = -1;
			if (l_deep <= 0) {
		 		mid_deep = 0 - l_deep;  
 				l_deep = mid_deep + 1;
			}
			if (mid_deep != -1) {
				root_val += x;
				update_aib (0, 1, +x);
				update_aib (0, mid_deep+1, -x);
			}
			if (l_deep <= h_deep) {
				update_aib (chain[v], l_deep+0, +x);
				update_aib (chain[v], h_deep+1, -x);
			}
		} else {
			int v;
			cin >> v;
			if (v == root) {
				cout << root_val << "\n";
				continue;
			}
			cout << query_aib (0, vertex_deep[v]) + query_aib (chain[v], vertex_deep[v]) << "\n";
		}

	}
	return 0;
}

void df_chain (int nod, int ch, int deep) {
	viz[nod] = true;
	
	chain_length[ch]++;
	chain[nod] = ch;
    vertex_deep[nod] = deep;

	FORIT (it, vertex[nod]) 
		if (viz[*it])
			;
		else
			df_chain (*it, ch, deep+1);
	return ;
}

