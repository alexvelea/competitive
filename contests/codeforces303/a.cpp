//Problem a from codeforces303
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

const int kMaxN = 105;

bool good[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
		good[i] = true;
		for (int j = 1; j <= n; ++j) {
			int init; cin >> init;
			if (init == 1 or init == 3) {
				good[i] = false;
			}
		}
	}
	vector<int> rez;
	for (int i = 1; i <= n; ++i) {
		if (good[i]) {
			rez.push_back(i);
		}
	}
	cout << rez.size() << '\n';
	for (auto itr : rez) {
		cout << itr << ' ';
	}
	return 0;
}
