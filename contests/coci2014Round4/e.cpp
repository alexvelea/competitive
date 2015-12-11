//Problem E from Codeforces Round coci.2014.round4
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

const int inf = 0x3f3f3f3f, kMaxN = 200005;

int sameParty[kMaxN];
bool party[kMaxN], bad[kMaxN], inside[kMaxN];
int stack[kMaxN], dr;

vector<int> vertex[kMaxN];

void check(int &nod) {
	if (sameParty[nod] > 2) {
		bad[nod] = true;
		if (inside[nod] == false) {
			stack[++dr] = nod;
			inside[nod] = true;
		}
	} else {
		bad[nod] = false;
	}
}

int main() {
	int n;
    cin >> n;
	for (int i = 1; i <= 5; ++i) {
   		int p;
		cin >> p;
		while (p--) {
			int a, b;
			cin >> a >> b;
			vertex[a].push_back(b);
			vertex[b].push_back(a);
		}
	} 

	for (int i = 1; i <= n; ++i) {
		sameParty[i] = vertex[i].size();
		if (sameParty[i] > 2) {
			bad[i] = true;
			inside[i] = true;
			stack[++dr] = i;
		}
	}
	
	while (dr > 0) {
		int nod = stack[dr--];
		inside[nod] = false;

		if (bad[nod]) {
			party[nod] ^= 1;
        	bad[nod] = false;
			sameParty[nod] = 0;

			for (int itr : vertex[nod]) {
				if (party[itr] == party[nod]) {
					sameParty[itr]++;
					sameParty[nod]++;
				} else {
					sameParty[itr]--;	
				}
				check(itr);
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << char('A' + party[i]);
	return 0;
}
