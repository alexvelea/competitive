#include <cassert>

#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream in("tarabe.in");
ofstream out("tarabe.out");

const int kMaxN = 200005;

int n, k;
int a[kMaxN], b[kMaxN];

bool solve(int64 mx) {
	int64 now = 0;
	for (int i = 1; i <= n and now < k; ++i) {
		if (a[i] <= mx) {
			now += 1LL * (mx - a[i]) / b[i];
			now++;
		}
	}
	if (now >= k)
		return true;
	return false;
}

int64 get_sum(int64 mx) {
	--mx;
	int remaining = k;
	int64 rez = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] <= mx) {
			int nr = (mx - a[i]) / b[i];
			nr++;
			rez += 1LL * nr * a[i];
			rez += 1LL * (nr) * (nr - 1) / 2 * b[i];
			remaining -= nr;
		}
	}
	assert(remaining >= 0);
	rez += 1LL * remaining * (mx + 1);
	return rez;
}

int main() {
	in >> n >> k;
	for (int i = 1; i <= n; ++i) {
		in >> b[i] >> a[i];
	}
	int64 rez = 0, p = 1LL << 40;
	for (; p; p/=2)
		if (solve(rez + p))
			;
		else
			rez += p;
	out << get_sum(rez + 1) << '\n';
	in.close();
	out.close();
	return 0;
}

