//Problem g from codeforcesLooksery
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

vector<int> ev;

int main() {
    ios::sync_with_stdio(false);
 	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x; x += i;
		ev.push_back(x);
	}
	sort(ev.begin(), ev.end());
	for (int i = 0; i < n; ++i) {
		ev[i] -= i + 1;
	}
	bool ok = true;
    for (int i = 1; i < n; ++i) {
		if (ev[i] < ev[i - 1]) {
			ok = false;
		}
	}
	if (not ok) {
		cout << ":(\n";
	} else {
     	for (auto itr : ev) {
			cout << itr << ' ';
		}
	}
	return 0;
}
