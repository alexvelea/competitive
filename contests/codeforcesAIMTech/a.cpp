// problem A from codeforces AIM Tech - 623
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 505, inf = 0x3f3f3f3f;

bool edge[kMaxN][kMaxN];
int color[kMaxN];

int n, m; 

void df(int nod) {
	for (int i = 1; i <= n; i += 1) {
		if (color[i] == 0) {
			if (edge[nod][i]) {
				color[i] = color[nod];
			} else {
				color[i] = 4 - color[nod];
			}
			df(i);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 1; i <= m; i += 1) {
		int a, b; cin >> a >> b;
		edge[a][b] = edge[b][a] = true;
	}

	for (int i = 1; i <= n; i += 1) {
		edge[i][i] = true;
		bool ok = true;
		for (int j = 1; j <= n; j += 1) {
			ok &= edge[i][j];
		}

		if (ok) {
			color[i] = 2;
		}
	}

	for (int i = 1; i <= n; i += 1) {
		if (color[i] == 0) {
			color[i] = 1;
			df(i);
		}
	}

	bool graph_is_ok = true;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= n; j += 1) {
			if (edge[i][j]) {
				graph_is_ok &= abs(color[i] - color[j]) <= 1;
			} else {
				graph_is_ok &= abs(color[i] - color[j]) >= 2;
			}
		}
	}

	if (graph_is_ok) {
		cout << "Yes\n";
		for (int i = 1; i <= n; i += 1) {
			cout << char(color[i] - 1 + 'a');
		}
	} else {
		cout << "No\n";
	}

	return 0;
}