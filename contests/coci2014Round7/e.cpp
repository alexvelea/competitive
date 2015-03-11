//Problem e from coci2014Round7
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 300005;

int64 sum[kMaxN];
int deq[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int n, k; cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}

	double rez = 0.0;
 	deq[1] = 0;
	int st = 1, dr = 0;
	for (int i = k; i <= n; ++i) {
		// add i - k
 		while (dr > st and 1.0 * (sum[deq[dr]] - sum[deq[dr - 1]]) * (deq[dr] - deq[dr - 1]) >= 1.0 * (sum[i - k] - sum[deq[dr]]) / ((i - k) - deq[dr]))
			--dr;
		deq[++dr] = i - k;

		// pop
		while (st < dr) {
			double c = 1.0 * (sum[i] - sum[deq[st]]) / (i - deq[st]);
			double c2 = 1.0 * (sum[i] - sum[deq[st + 1]]) / (i - deq[st + 1]);
			if (c2 > c) {
				++st;
			} else {
				break;
			}
		}
		double c = 1.0 * (sum[i] - sum[deq[st]]) / (i - deq[st]);
		if (c > rez) {
			rez = c;
		}
//		cerr << st << '\t' << dr << '\t' << deq[st] << '\n';
//		cerr << rez << "\n\n";
	}

	cout << fixed << setprecision(6) << rez << '\n';

	return 0;
}
