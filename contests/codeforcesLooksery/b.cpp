//Problem b from codeforcesLooksery
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
vector<int> selected;

char el[105][105];
int init[105], target[105];

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> el[i][j];
		}
	}

	for (int i = 1; i <= n; ++i) {
		cin >> target[i];
	}

	while (1) {
		bool findBad = false;
		int where = 0;
		for (int i = 1; i <= n; ++i) {
			if (init[i] == target[i]) {
				findBad = true;
				where = i;
			}
		}
		if (findBad == false) {
			break;
		}
		for (int i = 1; i <= n; ++i) {
			if (el[where][i] == '1') {
				init[i]++;
			}
		}
		selected.push_back(where);
	}
	cout << selected.size() << '\n';
	sort(selected.begin(), selected.end());
	for (auto itr : selected) {
		cout << itr << ' ';
	}
	return 0;
}
