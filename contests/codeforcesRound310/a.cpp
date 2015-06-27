//Problem a @ 27-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    int rez = 0;
    for (int i = 1; i <= m; ++i) {
        int x; cin >> x;
        int last = 0;
        while (x--) {
            int v; cin >> v;
            if (v != last + 1) {
                rez += 2;
            } else {
                last = v;
            }
        }
        if (last == 0) {
            --rez;
        }
    }
    cout << rez << '\n';

	return 0;
}
