#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int kMaxN = 2005;

#define int64 long long

int64 rez = 0;

void rotate(vector<string> &el) {
	vector<string> _el(el[0].size());
	for (int j = 0; j < int(el[0].size()); ++j) {
		for (int i = 0; i < int(el.size()); ++i) {
			_el[el[0].size() - j - 1]+=el[i][j];
		}
	}
	el = _el;
}

void solve(vector<string> &el) {
	vector<int64> dp[2];
	for (int j = 0; j < 2; ++j)
		dp[j].resize(el[0].size());

 	for (int i = 0; i < int(el[0].size()); ++i) {
		if (el[0][i] == '.')
			dp[0][i] = 1;
	}
	vector<bool> ok(el[0].size(), true);
	for (int l = 0; l < int(el.size()); ++l) {
//		cerr << l << "!!\n";
		for (int i = 0; i < int(el[0].size()); ++i) {
			if (el[l][i] == '#') {
				dp[0][i] = dp[1][i] = 0;
				ok[i] = false;
			}
		}

		if (l != 0 and l + 1 != int(el.size())) {
			for (int st = 0; st < int(el[0].size()); ) {
				if (el[l][st] == '#') {
					++st;
					continue;
				}

				int dr = st;
				while (dr < int(el[0].size()) and el[l][dr] == '.') { 
					++dr;
				}
				int64 sum = 0, sum2 = 0;
				for (int i = st; i < dr; ++i) {
					sum += dp[0][i];
					if (ok[i] and i != 0 and i + 1 != int(el[0].size()))
						sum2 += dp[0][i];
				}

                for (int i = st; i < dr; ++i) {
					int64 s = sum2;
					if (i == 0 or i + 1 == int(el[0].size()))
						continue;
					for (int j = -1; j <= 1; ++j) {
						if (i + j >= 0 and i + j < int(el[0].size()) and ok[i + j])
							s -= dp[0][i + j];
					}
					rez += s;
				}

				if (st == 0) {
					rez += sum;
				}
				if (dr == int(el[0].size())) {
					rez += sum;
				}
				for (int i = st; i < dr; ++i) {
					dp[1][i] += sum - dp[0][i];
				}
				st = dr;
			}
		}
	


		dp[0][0] = dp[1][0] = dp[0][el[0].size() - 1] = dp[1][el[0].size() - 1] = 0;

//  	for (int i = 0; i < int(el[0].size()); ++i) {
//			cerr << dp[0][i] << '|' << dp[1][i] << '\t';
//		}
//		cerr << '\n';   	   	
		
		if (l + 1 != int(el.size())) {
		} else {
			for (int i = 0; i < int(el[0].size()); ++i)
				rez += dp[0][i] + dp[1][i];
		}
//     	cerr << rez << '\n';   	
	}
/*	cerr << rez << '\n';
	for (auto itr : el) {
		for (auto itr2 : itr) {
			cout << itr2;
		}
		cout << '\n';
	}
	cout << '\n';*/
}

int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<string> el(n);
	for (int i = 0; i < n; ++i) {
		cin >> el[i];
	}
	el[0][0] = el[0][m - 1] = el[n - 1][m - 1] = el[n - 1][0] = '#';
	for (int i = 0; i < 4; ++i) {
		solve(el);
		for (auto itr : el)
			cerr << itr << '\n';
		cerr << "\n\n\n";
		rotate(el);
	}
	cout << rez / 2;
}
