#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n, m;
	int el[100][100];
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
			cin >> el[i][j];
	for (int i = 1; i <= n; ++i)
		if (el[i][1] == 1 || el[i][m] == 1) {
			cout << '2';
			return 0;
		}
    for (int j = 1; j <= m; ++j)
		if (el[1][j] == 1 || el[n][j] == 1) {
			cout << '2';
			return 0;
		}
	cout << '4';
	return 0;
}
