#include <fstream>
#include <iostream>
using namespace std;

ifstream in("rompetrol.in");
ofstream out("rompetrol.out");

#define ll long long

const ll inf = 1LL * 0x3f3f3f3f * 0x3f3f3f3f;
const int max_n = 100005;

int n, k, d[max_n], c[max_n], a[max_n];
ll best[max_n], last_best[max_n];

ll solve (int st, int mid, int dr) {
	ll rez = 0;
 	for (; st <= dr; ++st) 
		rez += 1LL * abs(d[mid] - d[st]) * c[st];
	return rez;
}

int main() {
 	in >> n >> k;
	for (int i = 1; i <= n; ++i)
		in >> d[i] >> c[i] >> a[i];
	for (int i = 0; i <= n; ++i)
		last_best[i] = best[i] = inf;
	last_best[0] = 0;
	for (int i = 1; i <= k; ++i) {
 		for (int dr = 1; dr <= n; ++dr)
			for (int st = 1; st <= dr; ++st)
				for (int mid = st; mid <= dr; ++mid) {
					ll x = solve (st, mid, dr);
					best[dr] = min(best[dr], last_best[st - 1] + x + a[mid]);
				}
		for (int j = 0; j <= n; ++j) {
			last_best[j] = best[j];
			best[j] = inf;
		}
	}
	out << last_best[n] << '\n';
	return 0;
}
