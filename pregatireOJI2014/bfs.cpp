#include <iostream>
using namespace std;

const int kMaxN = 1005;

int main() {
	int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			fin >> el[i][j];
		}
	}

	int x, y; cin >> x >> y;
	int a, b; cin >> a >> b;

	viz[x][y] = true;
	int st = 1, dr = 1;
	X[1] = x;
	Y[1] = y;

	while (st <= dr) {
		int x = X[st];
		int y = Y[dr];
		
	}
	return 0;
}
