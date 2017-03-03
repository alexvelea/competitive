#include <iostream>
#include <vector>
#include <algorithm>

#define maxn 31

using namespace std;

int n, m;
char a[maxn][maxn], b[maxn][maxn];
int sa[maxn], sb[maxn];
int viz[maxn];
int sum, neighbours, cnt, conf;
bool ok[1<<20];

void add(int i, int lim, char a[][maxn], int sa[]) {
	conf ^= (1<<(i-1));
	++cnt;
	sum += sa[i];
	int o_lim = (lim == n ? m : n);
	for (int j = 1; j <= o_lim; ++j) {
		if (a[i][j] == '1') {
			++viz[j];
			if (viz[j] == 1)
				++neighbours;
		}
	}
}

void remove(int i, int lim, char a[][maxn], int sa[]) {
	conf ^= (1<<(i-1));
	--cnt;
	sum -= sa[i];
	int o_lim = (lim == n ? m : n);
	for (int j = 1; j <= o_lim; ++j) {
		if (a[i][j] == '1') {
			--viz[j];
			if (viz[j] == 0)
				--neighbours;
		}
	}
}

void back(int k, int lim, char a[][maxn], int sa[], vector<int>& sol) {
	if (k == lim+1) {
		bool good = true;
		for (int i = 0; i < lim; ++i) {
			if ((conf>>i)&1) {
				good &= ok[(conf^(1<<i))];
			}
		}
		ok[conf] = good && (cnt <= neighbours);
		if (ok[conf]) {
			sol.push_back(sum);
		}
		return;
	}

	back(k+1, lim, a, sa, sol);

	add(k, lim, a, sa);
	back(k+1, lim, a, sa, sol);
	remove(k, lim, a, sa);
}

void solve() {
	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i] + 1;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			b[j][i] = a[i][j];
		}
	}

	for (int i = 1; i <= n; ++i) {
		cin >> sa[i];
	}

	for (int i = 1; i <= m; ++i) {
		cin >> sb[i];
	}

	int t;
	cin >> t;

	vector<int> sol1, sol2;

	back(1, n, a, sa, sol1);
	// for (auto el : sol1) {
	// 	cout << el << " ";
	// }
	// cout << "\n";
	back(1, m, b, sb, sol2);

	sort(sol1.begin(), sol1.end());
	sort(sol2.begin(), sol2.end());

	int i = 0, j = sol2.size()-1;
	long long ans = 0;
	for (; i < sol1.size(); ++i) {
		while (j >= 0 && sol1[i] + sol2[j] >= t)
			--j;
		ans += sol2.size()-1 - j;
	}

	cout << ans << "\n";
}

int main() {
	int k = 1;
	for (; k <= 1; ++k) {
		solve();
	}
}