#include <fstream>
#include <iostream>
using namespace std;

ifstream in("sum2.in");
ofstream out("sum2.out");

const int kMaxN = 100005;
int deq[kMaxN], sum[kMaxN];

int main() {
	int n, l, u;
	in >> n >> l >> u;
	for (int i = 1; i <= n; ++i) {
		in >> sum[i];
		sum[i] += sum[i - 1];
	}

	int st = 1, dr = 0, mx = -0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		if (deq[st] == i - u - 1)
			++st;
		int ind = i - l;
		if (ind >= 0) {
			while (st <= dr and sum[deq[dr]] >= sum[ind])
				--dr;
 			deq[++dr] = ind;
		}
		if (st <= dr) {
			mx = max(mx, sum[i] - sum[deq[st]]);
		}
	}
	out << mx << '\n';
}
