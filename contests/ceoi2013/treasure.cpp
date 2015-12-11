#include <iostream>
using namespace std;

int n;

int sum[200][200];

void query(int x1, int y1, int x2, int y2) {
	cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) {
			query(1, 1, i, j);
			cin >> sum[i][j];
		}
	cout << "END" << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
	 		if (sum[i][j] + sum[i-1][j-1] - sum[i][j-1] - sum[i-1][j])
				cout << '1';
			else
				cout << '0';
		}
		cout << endl;
	}
	return 0;
}
