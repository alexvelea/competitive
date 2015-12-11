#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

ifstream in("typ10d.in");
ofstream out("printer.out");

void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

string rez;

struct trie_nod {
	int max_deep, times;
	char c;
	trie_nod *it[26];

	trie_nod() {
		max_deep = 0;
		times = 0;
		c = 'a';
		for (int i = 0; i < 26; ++i)
 			it[i] = NULL;
	}
	void insert(string s, int mx) {
 		if (s.size() == 0) {
		    ++times;
			return ;
		}
		int c = s[s.size() - 1];
		if (it[c - 'a'] == NULL) {
			trie_nod *it_new = new(trie_nod);
			it[c - 'a'] = it_new;
			it_new -> c = c;
		}
		get_max(max_deep, mx);
		s.erase(s.end() - 1);
		it[c - 'a'] -> insert(s, mx);
	}
	void write() {
		rez += c;
		for (int i = 1; i <= times; ++i)
			rez += 'P';
		int mx = -1, poz = -1;
		for (int i = 0; i < 26; ++i)
			if (it[i] != NULL && it[i]->max_deep > mx) {
				mx = it[i]->max_deep;
				poz = i;
			}
		for (int i = 0; i < 26; ++i)
			if (it[i] != NULL && i != poz)
				it[i] -> write();
		if (poz != -1)
			it[poz]->write();
    	rez += '-';
	}
} trie;

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		string t;
		in >> t;
		reverse(t.begin(), t.end());
		trie.insert(t, t.size());
	}
	trie.write();
	n = rez.size();
	n--;
	while (rez[n] == '-')
		--n;
 	out << n << '\n';
	for (int i = 1; i <= n; ++i)
		out << rez[i] << '\n';
	return 0;
}
