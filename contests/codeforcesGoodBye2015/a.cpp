//Problem a @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

vector<int> days = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	string txt; cin >> txt >> txt;
	int rez = 0;
	if (txt[0] == 'm') {
		for (auto itr : days) {
			if (itr >= n) {
				rez += 1;
			}
		}
	} else {
		int x = 366 + 4;
		if (n <= 4) {
			rez -= 1;
		}

		rez += int((x - (n - 1) + 6) / 7);
	}
	cout << rez << '\n';
	return 0;
}
