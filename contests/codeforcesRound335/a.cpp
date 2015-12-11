
//Problem a @ 09-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5;
const double eps = 1e-7;

#define int64 long long

int position[kMaxN];
vector<int> el;

int mx = 0;

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; i += 1) {
		int x; cin >> x;
		el.push_back(x);
		position[x] = i;
	}

	sort(el.begin(), el.end());
	int current = 1;
	for (int i = 0; i + 1 < int(el.size()); i += 1) {
		if (position[el[i]] < position[el[i + 1]]) {
			current += 1;
		} else {
			if (current >= mx) {
				mx = current;
			}
			current = 1;
		}
	}
	if (current >= mx) {
		mx = current;
	}
	cout << n - mx << '\n';
	return 0;
}
