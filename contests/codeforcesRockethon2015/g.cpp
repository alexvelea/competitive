#include <iostream>
#include <iomanip>
using namespace std;

int el[100005];

double dp[205][100][100];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> el[i]; 
	for (int c1 = 1; c1 <= n; ++c1)
		for (int c2 = c1 + 1; c2 <= n; ++c2)
			dp[0][c1][c2] = 1.0;
	for (int K = 1; K <= k; ++K) {
 		for (int st = 1; st <= n; ++st)
			for (int dr = st + 1; dr<= n; ++dr) {
    			for (int c1 = 1; c1 <= n; ++c1) {
					for (int c2 = c1; c2 <= n; ++c2) {
//						cerr << '\n';
//						cerr << st << '\t' << dr << '\t' << c1 << '\t' << c2 << ">>>>\t";
						if (c1 <= st and dr <= c2) {
							int x = n - (n - c2 + (st - c1));
							int y = c2 - dr + (c1);
//							cerr << "A\t" << y << '\t' << x;
//							assert(y <= x);
							dp[K][st][dr] += 1.0 - dp[K - 1][y][x];

//						cerr << '\t' << dp[K][st][dr];
							continue;
						}
						if (c1 <= st and st <= c2) {
							int x = c1 + (c2 - st);
// 							cerr << "B\t" << x << '\t' << dr;   						
							dp[K][st][dr] += dp[K - 1][x][dr];
							
//						cerr << '\t' << dp[K][st][dr];
							continue;
						}
						if (c1 <= dr and dr <= c2) {
							int y = c1 + (c2 - dr);
// 							cerr << "C\t" << st << '\t' << y;   						
							dp[K][st][dr] += dp[K - 1][st][y];
							
//						cerr << '\t' << dp[K][st][dr];
							continue;
						}
						dp[K][st][dr] += dp[K - 1][st][dr];
//                        cerr << "D\t";
//						cerr << '\t' << dp[K][st][dr];
					}
				}
				dp[K][st][dr] /= 1.0 * n * (n + 1) / 2.0;
//				cerr << "~~~~\t" << st << '\t' << dr << '\t' << dp[K][st][dr] << "\n";
 	   		}
	}
//	cerr << "\n\n";
//	for (int st = 1; st <= n; ++st)
//		for (int dr = st + 1; dr <= n; ++dr) {
//			cerr << st << '\t' << dr << '\t' << dp[k][st][dr] << '\n';
//		}

	double rez = 0.0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (el[i] > el[j])
				rez += dp[k][i][j];
			else
				rez += 1 - dp[k][i][j];
		} 
	}	
	cout << fixed << setprecision(12) << rez << '\n';
	return 0;
}
