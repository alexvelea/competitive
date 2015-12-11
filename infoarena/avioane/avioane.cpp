#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("avioane.in");
ofstream out("avioane.out");

const int kMaxN = 100005;

#define ll long long

ll best[2][kMaxN], el[kMaxN], n;

int deq[kMaxN];
int st, dr;

double calc(int a, int b) {
	return 1.0 * (best[0][b] - best[0][a]) / (b - a);
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	sort(el + 1, el + n + 1);
	reverse(el + 1, el + n + 1);
	for (int i = 1; i <= n; ++i)
		best[0][i] = el[i] * i;
	ll mx = 0, mx2 = 0;
	st = 1;
	dr = 0;
	for (int i = 1; i <= n; ++i) {
		while (st < dr and calc(deq[st], deq[st + 1]) >= el[i]) 
				++st;
		best[1][i] = best[0][deq[st]] + 1LL * (i - deq[st]) * el[i];

		if (best[0][i] > mx2) {
			while (dr > st and
				calc(deq[dr], i) >= calc(deq[dr - 1], deq[dr]))
				--dr;
	 		deq[++dr] = i;
			mx2 = best[0][i];
		}

		if (best[1][i] > mx)
			mx = best[1][i];
	}
	out << mx << '\n';
	return 0;
}
