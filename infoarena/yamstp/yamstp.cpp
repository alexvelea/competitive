//Problem yamstp from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 25055;

int find(TrieNode *nod, char sir[]) {
	if (sir[0] == '\0') {
		return true;
	}
	find(nod->child[sir[0] - 'a'], sir + 1);
}

ifstream fin("yamstp.in");
ofstream fout("yamstp.out");

struct TrieNode {
	int child[2];
	TrieNode() {
		child[0] = child[1] = -1;
	}
};

struct Trie {
	TrieNode ind[21 * kMaxN];
	int next;
	Trie() {
		next = 1;
	}
	void clear() {
		ind[0] = TrieNode();
		next = 1;
	}

	void insert(int nr, int nod = 0, int bit = 20) {
		if (bit == -1) {
			return ;
		}
		int a = (nr & (1 << bit)) != 0;
		if (ind[nod].child[a] == -1) {
			ind[nod].child[a] = next;
			ind[next++] = TrieNode();
		}
		insert(nr, ind[nod].child[a], bit - 1);
	}

	int find(int nr, int nod = 0, int bit = 20) {
		if (bit == -1) {
			return 0;
		}
		int a = (nr & (1 << bit)) != 0;
		if (ind[nod].child[a] == -1) {
			return ((1) << bit) + find(nr, ind[nod].child[a ^ 1], bit - 1);
		} else {
			return find(nr, ind[nod].child[a], bit - 1);
		}
	}
} trie;


int el[kMaxN];

int brutSolve(int st, int c, int dr) {
	int mn = inf;
//	cerr << c - st << '\t' << dr - c + 1 << '\n';
	for (int i = st; i < c; ++i) {
		for (int j = c; j <= dr; ++j) {
			if ((el[i] ^ el[j]) < mn) {
 				mn = el[i] ^ el[j];
			}
		}
	}
	return mn;
}

int trieSolve(int st, int c, int dr) {
	trie.clear();
	for (int i = st; i < c; ++i) {
		trie.insert(el[i]);
	}
	int mn = inf;
//	cerr << '\t' << st << '\t' << dr << '\n';
	for (int i = c; i <= dr; ++i) {
		int x = trie.find(el[i]);
//		cerr << el[i] << '\t' << x << '\n';
		if (x < mn) {
			mn = x;
		}
	}
	return mn;
}

int merge(int st, int dr, int bit = 20) {
//	cerr << st << '\t' << dr << '\t' << bit << '\n';
	if (bit == -1) {
		return 0;
	}

	int c = st;
	while (c <= dr and (el[c] & (1 << bit)) == 0) {
		++c;
	}
	if (c == st) {
		return merge(st, dr, bit - 1);
	} else if (c == dr + 1) {
		return merge(st, dr, bit - 1);
	} else {
		int cost = 0;
		cost += merge(st, c - 1, bit - 1);
		cost += merge(c, dr, bit - 1);
      	int n = c - st, m = dr + 1 - c;
		if (n * m < (n + m) * 80) {
			cost += brutSolve(st, c, dr);
		} else {
			cost += trieSolve(st, c, dr);
		}
		return cost;
	}
}

int main() {
	int t; fin >> t;
	while (t--) {
		int n; fin >> n;
		for (int i = 1; i <= n; ++i) {
			fin >> el[i];
		}
		sort(el + 1, el + n + 1);
		fout << merge(1, n) << '\n';
	}
	return 0;
}
