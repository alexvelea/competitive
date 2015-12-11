//Problem #D from Codeforces code_strike_2014_finals
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 1000005;

int aib[2 * kMaxN];

int x[kMaxN], poz[kMaxN];
int el[2 * kMaxN];
bool first[kMaxN];

void aib_update(int ind, int val) {
	while (ind < 2 * kMaxN) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
	return ;
}

int aib_search(int val) {
	int p = 20;
	int rez = 0;
 	for (; p >= 0; --p)
		if ((1 << p) + rez < 2 * kMaxN)
			if (aib[(1 << p) + rez] < val) {
            	val -= aib[(1 << p) + rez];
				rez += (1 << p);
			}
	return rez + 1;
}

int main() {
	int n, m;
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
    	cin >> x[i] >> poz[i];
	
	int st = m + 2;
	for (int i = st; i < st + n; ++i) {
		el[i] = 0;
		aib_update(i, +1);
	}
	
	bool ok = true;

	for (int i = 1; i <= m and ok; ++i) {
		st--;
		int p = aib_search(poz[i]);
		if (first[x[i]] == false) {
			if (el[p] != false)
				ok = false;
			el[p] = x[i];
			first[x[i]] = true;

			el[st] = x[i];
			aib_update(p, -1);
			aib_update(st, +1);
		} else {
			if (el[p] != x[i])
				ok = false;
			aib_update(p, -1);
			aib_update(st, +1);
			el[st] = x[i];
		}
	}
	if (not ok) 
		cout << "-1\n";
	else {
		int st = m + 2;
		int dr = 1;
		for (int i = st; i < st + n; ++i)
			if (el[i] == 0) {
            	while (first[dr] != 0)
					++dr;
				cout << dr << ' ' ;
				++dr;
			} else {
				cout << el[i] << ' ';
			}
	}
	return 0;
}

