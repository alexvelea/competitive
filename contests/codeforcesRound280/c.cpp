//Problem C from Codeforces Round 280
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

priority_queue<pair<int, int> > pq;

int main() {
	int n, r, avg;
	cin >> n >> r >> avg;
	avg *= n;
	for (int i = 1; i <= n; ++i) {
		int a, b;
		cin >> a >> b;
		avg -= a;
		pq.push(make_pair(-b, r - a));
	}
	int64 rez = 0;
	while (avg > 0) {
		pair<int, int> tp = pq.top();
		pq.pop();
		tp.first *= -1;
		rez += 1LL * tp.first * min(avg, tp.second);
		avg -= tp.second;
	}
	cout << rez << '\n';
	return 0;
}
