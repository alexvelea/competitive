//Problem a from coci2014Round7
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 25;

int cost[kMaxN], ap[kMaxN];
int menuItem[5];

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> cost[i];
	}
	int menuCost; cin >> menuCost;
	for (int i = 1; i <= 4; ++i) {
		cin >> menuItem[i];
	}
	int m; cin >> m;
	while (m--) {
		int el; cin >> el;
		ap[el]++;
	}

	int rez = 0;

	while (1) {
		int c = 0;
		for (int i = 1; i <= 4; ++i) {
			if (ap[menuItem[i]]) {
				c += cost[menuItem[i]];
			}
		}
		if (c >= menuCost) {
			rez += menuCost;
			for (int i = 1; i <= 4; ++i) {
				if (ap[menuItem[i]]) {
					ap[menuItem[i]]--;
				}
			}
		} else {
			break;
		}
	}

	for (int i = 1; i <= n; ++i) {
		rez += ap[i] * cost[i];
	}

	cout << rez << '\n';
	return 0;
}
