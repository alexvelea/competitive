//Problem a @ 21-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

map<string, int> m;

int main() {
	ios::sync_with_stdio(false);
    int n, target; cin >> n;
    target = n / 2 + 1;
    for (int i = 1; i <= n; ++i) {
        string txt; cin >> txt;
        m[txt] += 1;
    }

    for (auto itr : m) {
        if (itr.second >= target) {
            cout << itr.first << '\n';
            return 0;
        }
    }
	return 0;
}
