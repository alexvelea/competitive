#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

ifstream in("basequery.in");
ofstream out("basequery.out");

const int kMaxN = 40005;
int el[kMaxN];

struct TrieNode {
    TrieNode* next[16];
    int val;
    ~TrieNode() {
        for (int i = 0; i < 16; ++i)
            if (next[i])
                delete next[i];
        //      delete this;
    }
    TrieNode() {
        for (int i = 0; i < 16; ++i)
            next[i] = NULL;
        val = 0;
    }
} *root = NULL;

vector<pair<string, int> > query[17];
char chr[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int get_number(char &c) {
    if (c >= '0' and c <= '9')
        return c - '0';
    return c - 'A' + 10;
}

void trie_insert(TrieNode* &nod, string &txt, int st, int dr, int val) {
    if (st == dr) {
		nod->val = val;   	
        return ;
	}
    
    int x = get_number(txt[st]);
    if (nod->next[x] == NULL) {
        nod->next[x] = new TrieNode();
    }
    trie_insert(nod->next[x], txt, st + 1, dr, val);
}

int64 rez[100005];
int beg[100005];

void trie_query(TrieNode* &nod, char txt[], int st, int dr, int val) {
	if (nod->val)
		rez[nod->val] += val;

    if (st == dr)
		return ;

    int x = get_number(txt[st]);
    if (nod->next[x] == NULL)
        return ;
   	trie_query(nod->next[x], txt, st + 1, dr, val);
}

unordered_map<string, int> ap;

int main() {
    int n, q;
    in >> n;
    for (int i = 1; i <= n; ++i)
        in >> el[i];
    
    in >> q;
    for (int i = 1; i <= q; ++i) {
        int b;
        string txt;
        in >> b >> txt;
		string t = txt;
		t += '#';
		t += char('a' + b);
		if (ap[t] != 0) {
			beg[i] = ap[t];
		} else {
	        query[b].push_back(make_pair(txt, i));
			ap[t] = i;
		}
    }
    
    for (int b = 2; b <= 16; ++b) {
        if (not query[b].size())
            continue;
        if (root)
            delete root;
        
        root = new TrieNode();
        for (int i = 0; i < int(query[b].size()); ++i)
			trie_insert(root, query[b][i].first, 0, query[b][i].first.size(), query[b][i].second);
        
		for (int i = 1; i <= n; ++i) {
            char txt[40];
            int x = el[i], itr = 0;
            while (x) {
                txt[itr] = chr[x % b];
                x /= b;
                ++itr;
            }
            
            reverse(txt, txt + itr);
            for (int j = 0; j < itr; ++j)
                trie_query(root, txt, j, itr, el[i]);
        }
        

    }
    
    for (int i = 1; i <= q; ++i)
		if (beg[i])
			out << rez[beg[i]] << '\n';
		else
	        out << rez[i] << '\n';
    return 0;
}
