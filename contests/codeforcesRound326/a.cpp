//Problem a @ 15-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxVal = 1e6 + 500;
const double eps = 1e-7;

#define int64 long long

int ap[kMaxVal + 5];

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        ap[x]++;
    }
    for (int i = 0; i < kMaxVal; ++i) {
        if (ap[i]) {
            ap[i + 1] += ap[i] / 2;
            ap[i] %= 2;
        }
    }
    int rez = 0;
    for (int i = 0; i < kMaxVal; ++i) {
        rez += ap[i];
    }
    cout << rez << '\n';
	return 0;
}
