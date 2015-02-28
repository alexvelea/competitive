//Problem B from Codeforces Round mindcodingRound1
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

map<string, pair<int, int> > team;

int main() {
    for (int i = 1; i <= 6; ++i) {
		string a, b;
		int x, y;
		cin >> a >> b >> x >> y;
		team[a].second -= x;
		team[b].second -= y;
		if (x == y) {
			team[a].first--;
			team[b].first--;
		}
		if (x > y) {
			team[a].first -= 3;
		}
		if (y > x) {
			team[b].first -= 3;
		}
	}
	vector<pair<pair<int, int>, string> > e;
	for (auto itr : team) {
		e.push_back(make_pair(itr.second, itr.first));
	}
	sort(e.begin(), e.end());
	for (int i = 0; i < 4; ++i) {
		cout << e[i].second << '\n';
	}
	return 0;
}
