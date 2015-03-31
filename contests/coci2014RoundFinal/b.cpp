//Problem b from coci2014RoundFinal
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 300005;

int compSmaller[kMaxN], nrComp, comp[kMaxN];
int goUp[kMaxN], goDown[kMaxN], rez[kMaxN];
vector<int> smaller[kMaxN], smallerComp[kMaxN], compEl[kMaxN], Equal[kMaxN];
bool viz[kMaxN];

void dfEqual(int nod) {
	viz[nod] = true;
	compEl[nrComp].push_back(nod);
	comp[nod] = nrComp;
	for (auto itr : Equal[nod]) {
		if (not viz[itr]) {
			dfEqual(itr);
		}
	}
}

vector<int> ord;

void dfComp(int nod) {
	ord.push_back(nod);
	for (auto itr : smallerComp[nod]) {
		compSmaller[itr]--;
		if (compSmaller[itr] == 0) {
			goDown[itr] = max(goDown[itr], goDown[nod] + 1);
			dfComp(itr);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
 	int n, m, v; cin >> m >> n >> v;
	for (int i = 1; i <= v; ++i) {
		string txt; cin >> txt;
		int a[2] = {0, 0}, ind = 0; 
		char c = ' ';
		for (int j = 0; j < int(txt.size()); ++j) {
			if (txt[j] == '=' or txt[j] == '<') {
				c = txt[j];
				++ind;
			} else {
				a[ind] *= 10;
				a[ind] += txt[j] - '0';
			}
		}

		if (c == '=') {
			Equal[a[0]].push_back(a[1]);
			Equal[a[1]].push_back(a[0]);
		} else {
			smaller[a[0]].push_back(a[1]);
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (not viz[i]) {
			++nrComp;
			dfEqual(i);
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (auto itr : smaller[i]) {
			smallerComp[comp[i]].push_back(comp[itr]);
			compSmaller[comp[itr]]++;
		}
	}

	for (int i = 1; i <= n; ++i) {
		viz[i] = false;
	}

	for (int i = 1; i <= nrComp; ++i) {
		if (compSmaller[i] == 0) {
			dfComp(i);
		}
	}
	reverse(ord.begin(), ord.end());
	for (auto itr : ord) {
		for (auto itr2 : smallerComp[itr]) {
			goUp[itr] = max(goUp[itr], 1 + goUp[itr2]);
		}
	}

 	for (int i = 1; i <= nrComp; ++i) {
		if (goUp[i] + goDown[i] == m - 1) {
			int r = goDown[i] + 1;
			for (auto itr : compEl[i])  {
				rez[itr] = r;
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (rez[i] == 0)
			cout << "?\n";
		else
			cout << "K" << rez[i] << '\n';
	}
	return 0;
}
