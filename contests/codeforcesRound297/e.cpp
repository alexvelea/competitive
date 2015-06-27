//Problem e from codeforcesRound297
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

map<int64, int> M[2][26];

int el[30];

void bt(int ind, int st, int dr, int k, int64 sum) {
    if (st == dr + 1) {
		M[ind][k][sum]++;
		return ;
	}
	if (el[st] <= 18) {
		int64 fact = 1;
		for (int i = 1; i <= el[st]; ++i)
			fact = 1LL * fact * i;
		bt(ind, st + 1, dr, k + 1, sum + fact);
	} 
 		bt(ind, st + 1, dr, k, sum);
		bt(ind, st + 1, dr, k, sum + el[st]); 
}

int main() {
	ios::sync_with_stdio(false);
	int64 s;
	int n, k; cin >> n >> k >> s;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
	}
	sort(el + 1, el + n + 1);
 	int ind;
	ind = n / 2;

	bt(0, 1, ind, 0, 0);
 	bt(1, ind + 1, n, 0, 0);

	int64 rez = 0;
	M[0][0][0] = M[1][0][0] = 1;
	for (int _k = 0; _k <= k; ++_k) {
		for (auto itr : M[0][_k]) {
			int64 rest = s - itr.first;
			for (int i = 0; i + _k <= k; ++i) {
				rez += 1LL * itr.second * M[1][i][rest];
			}
		}
	}

	cout << rez << '\n';
	return 0;
}
