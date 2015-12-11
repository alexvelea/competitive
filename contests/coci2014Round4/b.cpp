//Problem B from Codeforces Round coci.2014.round4
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int64 st[kMaxN], dr[kMaxN];
int el[kMaxN];
pair<int, int> nr[kMaxN]; int nrEl;

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
	}
	sort(el + 1, el + n + 1);
	for (int st = 1; st <= n; ) {
		int dr = st;
		while (dr <= n and el[st] == el[dr])
			++dr;
		nr[++nrEl] = make_pair(el[st], dr - st);
		st = dr;
	}
	
	for (int64 i = 1, sum = 0, rez = 0; i <= n; ++i) {
		sum += nr[i].second;
		rez += 1LL * sum;
 		st[i] = rez;   	
	}

 	for (int64 i = n, sum = 0, rez = 0; i; --i) {
		sum += nr[i].second;
		rez += 1LL * sum;
 		dr[i] = rez;   	
	}

	if (nrEl <= 2) {
		cout << "Slavko\n";
		if (nrEl == 1) 
			cout << nr[1].first << ' ' << nr[1].second << '\n';
		else
 			cout << nr[1].first << ' ' << nr[2].second << '\n';
	} else {
		int St = 1, Dr = n;
		bool winner = false;
		while (Dr - St > 1) {
			if (st[St] <= dr[Dr])
				St++, winner = 0;
			else
				Dr--, winner = 1;
		}

		if (winner == 0)
			cout << "Mirko\n";
		else
			cout << "Slavko\n";
		cout << nr[St].first << ' ' << nr[Dr].first << '\n';

	}
	return 0;
}
