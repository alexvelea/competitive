//#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

ifstream cin("dirichlet.in");
ofstream cout("dirichlet.out");

int ap[6], l[6];
int dp[66][66][66][66]; 

inline void getMin(int &a, int &b) {
	a = a < b ? a : b;
}

int main() {
	int t, n;
	int sum = 0, target;
	cin >> n >> t;
	for (int i = 0; i < n; ++i) {
		cin >> ap[i] >> l[i];
		if (ap[i] == 0)
			l[i] = 0;
		sum += ap[i] * l[i];
	}

	if (sum % t) {
		cout << "No\n";
		return 0;
	}

	target = sum / t;

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (ap[j] * l[j] >= ap[i] * l[i]) {
				swap(ap[i], ap[j]);
				swap(l[i], l[j]);
			}
		}
	}

	for (int a = 0; a <= ap[0]; ++a)
		for (int b = 0; b <= ap[1]; ++b)
			for (int c = 0; c <= ap[2]; ++c)
				for (int d = 0; d <= ap[3]; ++d) {
					dp[a][b][c][d] = ap[4] + 1;
				}
	dp[0][0][0][0] = 0;
	for (int T = 1; T <= t; ++T) {
 		for (int a = 0; a <= ap[0]; ++a)
			for (int b = 0; b <= ap[1]; ++b)
				for (int c = 0; c <= ap[2]; ++c)
					for (int d = 0; d <= ap[3]; ++d) {
 						int sum = a * l[0] + b * l[1] + c * l[2] + d * l[3];
						if (sum > T * target) {
							while (d <= ap[3]) {
								dp[a][b][c][d] = ap[4] + 1;
								++d;
							}
							break;
						}
						if (sum + l[4] * ap[4] + (ap[3] - d) * l[3] < (T - 1) * target) {
							break;
						} 

						if (dp[a][b][c][d] > ap[4]) 
							continue;

						sum += dp[a][b][c][d] * l[4];
						if (sum > T * target) {
							dp[a][b][c][d] = ap[4] + 1;
							continue;
						}
						
						getMin(dp[a + 1][b][c][d], dp[a][b][c][d]);
						getMin(dp[a][b + 1][c][d], dp[a][b][c][d]);
						getMin(dp[a][b][c + 1][d], dp[a][b][c][d]);
						getMin(dp[a][b][c][d + 1], dp[a][b][c][d]);

						// cazul cand nu avem 5 elemente
						if (ap[4] == 0) {
							if (sum == T * target) {
								dp[a][b][c][d] = 0;
							} else {
								dp[a][b][c][d] = ap[4] + 1;
							}

							continue;
						}

						int last = T * target - sum;
						if (last % l[4]) {
							dp[a][b][c][d] = ap[4] + 1;
						} else {
							dp[a][b][c][d] += last / l[4];
						}
					}
	}

	if (dp[ap[0]][ap[1]][ap[2]][ap[3]] != ap[4]) {
		cout << "No\n";
	} else {
		cout << "Yes\n";
	}
	
	return 0;
}
