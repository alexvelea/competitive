//Problem B from Codeforces Round usaco2015FebGold
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

ifstream in("censor.in");
ofstream out("censor.out");

const int inf = 0x3f3f3f3f;

struct TrieNode {
	int len;
	bool finish;
	TrieNode *next[26], *back;
	TrieNode(int _len = 0) {
		len = _len;
		finish = 0;
		for (int i = 0; i < 26; ++i) {
			next[i] = NULL;
		}
	}
} *root = new TrieNode;

void insertTrie(TrieNode *now, char *a) {
	if (*a == 0) {
		now->finish = true;
		return ;
	}
	if (now->next[*a - 'a'] == NULL) {
		now->next[*a - 'a'] = new TrieNode(now->len + 1);
	}
	insertTrie(now->next[*a - 'a'], a + 1);
}

int main() {
	int n;
	string txt, aux;
    in >> aux;
	txt = ' ';
	txt += aux;

	in >> n;
	for (int i = 1; i <= n; ++i) {
		string bad;
		in >> bad;
		bad[i] += '\0';
		insertTrie(root, &bad[0]);
	}

	queue<TrieNode*> Q;
	Q.push(root);
	while (Q.size()) {
		TrieNode *now = Q.front(); Q.pop();
		for (int i = 0; i < 26; ++i) {
			TrieNode* back = now->back;
			while (back != NULL and back->next[i] == NULL)
				back = back->back;

			if (now->next[i] == NULL) {
				if (back == NULL) {
					now->next[i] = root;
				} else {
					now->next[i] = back->next[i];
				}
			} else {
				if (back == NULL) {
					now->next[i]->back = root;
				} else {
					now->next[i]->back = back->next[i];
				}
				Q.push(now->next[i]);
			}
		}
	}
	
	vector<TrieNode*> best(txt.size());
	string word = "";
	best[0] = root;

	for (int i = 1; i < int(txt.size()); ++i) {
		TrieNode *now = best[word.size()];
 		word += txt[i];   	

		while (now != NULL and now->next[txt[i] - 'a'] == NULL)
			now = now->back;

		if (now == NULL) {
			now = root;
		} else {
			now = now->next[txt[i] - 'a'];
		}
		best[word.size()] = now;
/* 		cerr << txt[i] << '\t' << now->len << '\t';   	
		for (int j = 0; j < 26; ++j)
			cerr << (now->next[j] != NULL);
		cerr << '\n';*/
		if (now->finish == true) {
			for (int i = 1; i <= now->len; ++i) {
				assert(word.size());
				word.pop_back();
			}
		}
	}

	out << word << '\n';
	return 0;
}
