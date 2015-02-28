//Problem A from Codeforces Round 290
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

string txt[100];

vector<int> edge[30];
int inside[30];
bool viz[30];
bool ok = true;

void solve(int st, int dr, int l = 0) {
	if (l == 100)
		return ;
	int cst = st;
	if (st == dr - 1)
		return ;
//	cerr << st << '\t' << dr << '\t' << l << '\n';
	for (; cst < dr; ) {
		int cdr = cst;
		while (cdr < dr and txt[cst][l] == txt[cdr][l]) {
			++cdr;
		}
		if (cst != st) {
//			cerr << txt[cst][l] << '\t' << txt[cst - 1][l] << "\t\t!!!\n";
			edge[txt[cst][l] - 'a'].push_back(txt[cst - 1][l] - 'a');
		}
		solve(cst, cdr, l + 1);
		cst = cdr;
	}
	return ;
}

void makeInside() {
	for (int i = 0; i < 27; ++i)
		inside[i] = 0;
 	for (int i = 0; i < 27; ++i) {
		if (not viz[i])
			for (auto itr : edge[i]) {
				if (not viz[itr]) {
					++inside[i];
				}
			}
	}
 
}

int main() {
	int n;
	int rez[30];
    cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> txt[i];
		while (txt[i].size() < 100) 
			txt[i] += char('z' + 1);
	}

	solve(0, n, 0);
	for (int i = 0; i < 26; ++i)
		edge[i].push_back(26);
	for (int k = 0; k < 27; ++k) {
		makeInside();
		bool find = false;
		for (int i = 0; i < 27; ++i) {
			if (inside[i] == 0 and not viz[i]) {
				rez[k] = i;
				viz[i] = true;
				find = true;
				break;
			}
		}
		if (find == false)
			ok = false;
	}
	if (ok == false) {
		cout << "Impossible\n";
	} else {
		for (int i = 0; i < 27; ++i)
			if (rez[i] < 26)
				cout << char(rez[i] + 'a');
	}
	return 0;
}
