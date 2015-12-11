//Problem C from Codeforces Round 293
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int here[kMaxN], where[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int n, m, k;
    cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> here[i];
		where[here[i]] = i;
	}
	int64 rez = 0;
	for (int i = 1; i <= m; ++i) {
		int el;
		cin >> el;
		int poz = where[el];
		rez += (poz - 1) / k + 1;
		if (where[el] == 1)
			continue;

		swap(here[poz], here[poz - 1]);
		where[here[poz]] = poz;
		where[here[poz - 1]] = poz - 1;
	}
	cout << rez << '\n';
	return 0;
}
//Problem C from Codeforces Round 293
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {

return 0;
}
