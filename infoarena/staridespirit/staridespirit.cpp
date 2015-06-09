//Problem staridespirit from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005, kMaxK = 35;

ifstream fin("starispirit.in");
ofstream fout("starispirit.out");

int task[kMaxN];
long double change[kMaxK][kMaxK], chx[kMaxK][kMaxN], start[kMaxK];

long double dp[kMaxK][kMaxN];
int father[kMaxK][kMaxN];

void lg(long double &a) {
	if (a == 0.0) {
		a = 100000000.0;
	} else {
		a = log(a);
	}
}

int n, k, m;

void normal(int day) {
	long double mn = dp[1][day];
	for (int i = 2; i <= k; ++i) {
		if (mn > dp[i][day]) {
			mn = dp[i][day];
		}
	}
	for (int i = 1; i <= k; ++i) {
		dp[i][day] -= mn;
	}
}

int main() {
	int t; fin >> t;
	while (t--) {
		fin >> n >> k >> m;
		for (int i = 1; i <= n; ++i) {
			fin >> task[i];
		}
		for (int i = 1; i <= k; ++i) {
			fin >> start[i];// lg(start[i]);
		}

        for (int i = 1; i <= k; ++i) {
			for (int j = 1; j <= k; ++j) {
				fin >> change[i][j];// lg(change[i][j]);
			}
		}

 		for (int i = 1; i <= k; ++i) {
			for (int j = 1; j <= m; ++j) {
				fin >> chx[i][j];// lg(chx[i][j]);
			}
		}

		for (int i = 1; i <= k; ++i) {
//			dp[i][1] = 0.0 + start[i] + chx[i][task[1]];
			dp[i][1] = 1.0 * start[i] * chx[i][task[1]];
    	}
	
		for (int day = 2; day <= n; ++day) {
			for (int i = 1; i <= k; ++i) {
				father[i][day] = 0;
				for (int j = 1; j <= k; ++j) {
/*					if (father[i][day] == 0 or dp[j][day - 1] + change[j][i] > dp[i][day]) {
						father[i][day] = j;
						dp[i][day] = dp[j][day - 1] + change[j][i];
					}*/

 					if (father[i][day] == 0 or dp[j][day - 1] * change[j][i] > dp[i][day]) {
						father[i][day] = j;
						dp[i][day] = dp[j][day - 1] * change[j][i];
					}
				}
//				dp[i][day] += chx[i][task[day]];
				dp[i][day] *= chx[i][task[day]];
			}
//			normal(day);
		}

		long double mx = dp[1][n]; int f = 1;
		for (int i = 1; i <= k; ++i) {
			if (mx < dp[i][n]) {
				mx = dp[i][n];
				f = i;
			}
		}

		vector<int> rez;
		for (int day = n; day; --day) {
			rez.push_back(f);
			f = father[f][day];
		}
		reverse(rez.begin(), rez.end());
		for (auto itr : rez) {
			fout << itr << ' ';
		}
		fout << '\n';
	}
	return 0;
}
