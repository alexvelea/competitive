//Problem e @ 09-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

const int kMaxN = 1e3 + 3;
const long double inf = 1e10;
const long double eps = 1e-10;

#define int64 long long

long double C[kMaxN], chx[kMaxN], cost[kMaxN];
long double road[kMaxN][kMaxN];

bool solved[kMaxN];

bool update(int i, int j) {
	if (road[j][i] == 0) {
		return false;
	}

	if (
		((((1 - chx[j]) * road[j][i] * (C[i] + 1) + cost[j]) / (chx[j] + (1 - chx[j]) * road[j][i]))
		+ 1 / (chx[j] + (1 - chx[j]) * road[j][i]) - 1) + eps < C[j]) {
		cost[j] += (C[i] + 1) * (1 - chx[j]) * road[j][i];
		chx[j] += (1 - chx[j]) * road[j][i];
		C[j] = cost[j] / chx[j] + 1 / chx[j] - 1;
		return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= n; j += 1) {
			int c; cin >> c;
			road[i][j] = 1.0 * c / 100;
		}
	}
	priority_queue<pair<long double, int> > pq;
	for (int i = 1; i <= n; i += 1) {
		chx[i] = 0;
		cost[i] = 0;
		C[i] = +inf;
	}
	C[n] = 0;
	chx[n] = 100;
	cost[n] = 0;

	pq.push({0.0, n});

	while (pq.size()) {
		int nod = pq.top().second;
		pq.pop();
		
		if (solved[nod]) {
			continue;
		}
		// cerr << "!\t" << nod << '\n';
		solved[nod] = true;

		for (int i = 1; i <= n; i += 1) {
			if (not solved[i]) {
				if (update(nod, i)) {
					pq.push({-C[i], i});
				}
			}
		}
		// for (int i = 1; i <= n; i += 1) {
			// cerr << C[i] << '\t' << chx[i] << '\t' << cost[i] << '\n';
		// }
	}

	cout << fixed << setprecision(15) << C[1] << '\n';

	return 0;
}
