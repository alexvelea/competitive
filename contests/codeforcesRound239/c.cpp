//Problem C from Codeforces Round 239
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
	int n, k, d; cin >> n >> k >> d;
	vector<int64> best(n), oldBest(n);
	vector<int> deq(n);
	best.assign(n, 0);

	int64 rez = 0, lastT = 0;

	while (k--) {
		int poz, v, t; cin >> poz >> v >> t; poz -= 1;
		rez += v;
		t = t - lastT;
		lastT += t;

		int D = min(1LL * t * d, 1LL * n);
 		
		oldBest.swap(best);
		int st = 0, dr = -1;
		for (int i = 0; i < D and i < n; ++i) {
			while (st <= dr and oldBest[deq[dr]] >= oldBest[i])
				--dr;
			deq[++dr] = i;
		}

		for (int i = 0; i < n; ++i) {
			if (i - deq[st] > D)
				++st;
			while (st <= dr and i + D < n and oldBest[deq[dr]] >= oldBest[i + D])
				--dr;
			if (i + D < n) {
				deq[++dr] = i + D;
			}

            best[i] = oldBest[deq[st]] + abs(poz - i);
		}
	}
	int64 mn = best[0];
	for (auto &itr : best)
		mn = min(mn, itr);
	rez -= mn;
	cout << rez << '\n';
	return 0;
}
