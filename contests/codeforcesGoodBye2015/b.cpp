//Problem b @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

vector<int64> R;

int main() {
	ios::sync_with_stdio(false);
	for (int i = 0; i < 63; i += 1) {
		for (int j = i - 1; j >= 0; j -= 1) {
			int64 rez = 0;
			rez += (1LL << i);
			rez -= 1;
			rez -= (1LL << j);
			rez += (1LL << i);
			R.push_back(rez);
		}
	}

	int64 a, b; cin >> a >> b;
	int rez = 0;
	for (auto itr : R) {
		if (a <= itr and itr <= b) {
			rez += 1;
		}
	}
	cout << rez << '\n';
	return 0;
}
