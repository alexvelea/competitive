//Problem B from Codeforces Round facebookHackerCup2015Round1
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

const int inf = 0x3f3f3f3f;

ifstream in("input.txt");
ofstream out("output.txt");

int rez = 0;

struct TrieNode {
	int under;
	TrieNode *next[26];
	TrieNode() {
		under = 0;
		for (int i = 0; i < 26; ++i)
			next[i] = NULL;
	}
	~TrieNode() {
		for (int i = 0; i < 26; ++i)
			if (next[i])
				delete(next[i]);
	}

    void Insert(string &txt) {
		if (txt.size() == 0 and under == 0)
			++rez;
        ++under;
		if (txt.size() == 0)
			return ;


		char c = txt[txt.size() - 1];
		txt.pop_back();
		if (next[c - 'a'] == NULL) {
			next[c - 'a'] = new(TrieNode);
		} else {
			rez++;
		}

		next[c - 'a']->Insert(txt);
	}
} ;

int main() {
	TrieNode *root;
    int t;
	in >> t;
	for (int T = 1; T <= t; ++T) {
		cerr << T << '\n';
		int n;
		root = new(TrieNode);
		rez = 0;
		in >> n;
		for (int i = 1; i <= n; ++i) {
			string word;
			in >> word;
			reverse(word.begin(), word.end());
			root->Insert(word);
//			cout << rez << '\n';
		}
//		delete(root);
		root = new(TrieNode);
		out << "Case #" << T << ": " << rez << '\n';
	}
	return 0;
}
