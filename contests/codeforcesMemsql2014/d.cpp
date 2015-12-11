//Problem D from Codeforces Round memsql
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

priority_queue<int> pq[3];

int main() {
	int k, n[3], t[3];
	cin >> k >> n[0] >> n[1] >> n[2] >> t[0] >> t[1] >> t[2];
	for (int i = 0; i < 3; ++i)
		for (int j = 1; j <= n[i]; ++j)
			pq[i].push(0);

	int mx = 0;

	for (int i = 1; i <= k; ++i) {
		int a = -pq[0].top();
		int b = -pq[1].top();
		int c = -pq[2].top();

		pq[0].pop(); pq[1].pop(); pq[2].pop();

		a += t[0];
		if (b > a) {
			a = b;
		} else {
			b = a;
		}

		b += t[1];

		if (c > b) {
			a += c - b;
			b += c - b;
		} else {
			c = b;
		}

		c += t[2];

		pq[0].push(-a);
		pq[1].push(-b);
		pq[2].push(-c);

		mx = c;
	}
	cout << mx << '\n';
	return 0;
}
