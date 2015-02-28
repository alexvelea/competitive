#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int kMaxN = 10005, kMaxS = 200005;

ifstream in("ratina.in");
ofstream out("ratina.out");

int nr_id = 0;

vector<int> vertexkMaxS];
int vertex_id[kMaxN];
string txt[kMaxN];

struct trie_node {
 	int id;
	trie_node *next[26];

	trie_node() {
		nr_id++;
		id = nr_id;
		for (int i = 0; i < 26; ++i)
			next[i] = NULL;
	}
} *base = new trie_node;

void trie_insert(trie_node *act, int poz) {
	act->next[poz] = new trie_node;
	int a = act->id;
	int b = act->next[poz]->id;
	vertex[a].push_back(b);
	assert(act->id < kMaxS);
}

void trie_insert(string txt, int ind) {
	trie_node *act = base;
	for (int i = 0; i < int(txt.size()); ++i) {
		int c = txt[i] - 'a';
		if (act->next[c] == NULL) {
			trie_insert(act, c);
		}
		act = act->next[c];
	}
	vertex_id[ind] = act->id;
}

int nr_df = 0, deep[kMaxS], rmq[20][2 * kMaxS];
int poz_st[kMaxS], poz_dr[kMaxS];


void df(int nod) {
	++nr_df;
	assert(nr_df < 2 * kMaxS- 100); 
//  rmq purpose
	poz_st[nod] = nr_df;
	rmq[0][nr_df] = nod;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		deep[vertex[nod][i]] = deep[nod] + 1;
		df(vertex[nod][i]);

		++nr_df;
		rmq[0][nr_df] = nod;
	}
	poz_dr[nod] = nr_df;
}

vector<int> srt;
bool my_srt(int a, int b) {
	return txt[a] < txt[b];
}

int lca(int st, int dr) {
	int d = 0;
	while (1<<d <= (dr - st + 1)) {
		++d;
	}
	--d;

/*	assert(d < 20);
	assert(st < 2 * kMaxS);
	assert(dr < 2 * kMaxS);*/
//	assert(st <= dr);

	int a = rmq[d][st];
	int b = rmq[d][dr - (1 << d) + 1];

//	assert(a < kMaxS);
//	assert(b < kMaxS);

	if (deep[a] < deep[b])
		return a;
	return b;
}


int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		in >> txt[i];
		srt.push_back(i);
	}
	sort(srt.begin(), srt.end(), my_srt);
	for (int i = 0; i < n; ++i)
		trie_insert(txt[srt[i]], srt[i]);
	df(1);
 	for (int l = 1; (1 << l) <= nr_df; ++l) 
		for (int st = 1; st + (1 << l) - 1 <= nr_df; ++st) {
			int dr = st + (1 << (l - 1));
			int a = rmq[l - 1][st];
			int b = rmq[l - 1][dr];
			if (deep[a] < deep[b])
				rmq[l][st] = a;
			else
				rmq[l][st] = b;
		}
//	for (int i = 1; i <= nr_df; ++i)
//		assert(poz_st[i] <= poz_dr[i]);
	while (m--) {
		int k;
		in >> k;
		int mn = 2 * kMaxS;
		int mx = 0;
		while (k--) {
			int a;
			in >> a;
			if (poz_dr[vertex_id[a]] > mx)
				mx = poz_dr[vertex_id[a]];
			if (poz_st[vertex_id[a]] < mn)
				mn = poz_st[vertex_id[a]];
		}
		out << deep[lca(mn, mx)] << '\n';
	}
	return 0;
}
