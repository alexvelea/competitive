//Problem B from Codeforces Round 290
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

unordered_map<int, int> best;
unordered_map<int, bool> inside;

int gcd(int a, int b) {
	if (a == 1 or b == 1)
		return 1;
	if (a == 0)
		return b;
	if (b == 0 )
		return a;
	return gcd(b, a % b);
}

int el[1000000];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> el[i];
		inside[el[i]] = true;
	}
	for (int i = 0; i < n; ++i) {
		int cost; cin >> cost;
		best[el[i]] = cost;
	}
	for (int i = 0; i < n; ++i) {
		int N = n;
		for (int j = i + 1; j < N; ++j) {
			int g = gcd(el[i], el[j]);
			int c = best[el[i]] + best[el[j]];
//			cerr << g << '\t' << c << '\n';
			if (best[g] == 0 or best[g] > c) {
				best[g] = c;
				if (inside[g])
					;
				else {
					inside[g] = true;
					el[n++] = g;
				}
			}
		}
	}
	if (best[1] == 0)
		best[1] = -1;
	cout << best[1];
	return 0;
}
