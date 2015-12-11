#include <iostream>
using namespace std;
int el[50][50], best[50][50];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			char c;
			cin >> c;
			if (c == 'a')
				el[i][j] = +1;
			if (c == 'b')
				el[i][j] = -1;
		}
	for (int i = n; i; --i) {
		best[n][i] = best[n][i + 1] + el[n][i];
		best[i][n] = best[i + 1][n] + el[i][n];
	}
	for (int i = n - 1; i; --i)
		for (int j = n - 1; j; --j) {
			if ((i + j) % 2 == 1) {
				// first player
			    best[i][j] = el[i][j] + max(best[i + 1][j], best[i][j + 1]);
			} else {
				best[i][j] = el[i][j] + min(best[i +1][j], best[i][j + 1]);
			}
		}
	if (best[1][1] > 0)
		cout << "FIRST";
	if (best[1][1] < 0)
		cout << "SECOND";
	if (best[1][1] == 0)
		cout << "DRAW";
	return 0;
}
