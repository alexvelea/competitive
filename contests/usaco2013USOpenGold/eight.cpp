#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int kMaxN = 305;
vector<string> txt;

ifstream in("input.txt");
ofstream out("output.txt");

int goUp[kMaxN][kMaxN], goRight[kMaxN][kMaxN];
int dp[kMaxN][kMaxN][kMaxN], up[kMaxN][kMaxN][kMaxN], down[kMaxN][kMaxN][kMaxN];

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

void solve() {
	for (int i = 0; i < int(txt.size()); ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st)
			for (int dr = 0; dr < int(txt[0].size()); ++dr) 
				dp[i][st][dr] = 0;
	}

	for (int i = 0; i < int(txt[0].size()); ++i) {
		if (txt[0][i] == '.') {
			goUp[0][i] = 1;
		} else {
			goUp[0][i] = 0;
		}
	}
	for (int i = 1; i < int(txt.size()); ++i) {
		for (int j = 0; j < int(txt[0].size()); ++j) {
			if (txt[i][j] == '.') {
				goUp[i][j] = goUp[i - 1][j] + 1;
			} else {
				goUp[i][j] = 0;
			}
		}
	}


	for (int i = 0; i < int(txt.size()); ++i) {
		int dr = 0;
		for (int j = (txt[0].size()) - 1; j >= 0; --j) {
			if (txt[i][j] == '.') {
				++dr;
			} else {
				dr = 0;
			}
			goRight[i][j] = dr;
		}
	}

	for (int i = 0; i < int(txt.size()); ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = st; dr < int(txt[0].size()) and txt[i][dr] == '.'; ++dr) {
				int h = min(goUp[i][st], goUp[i][dr]);
				getMax(dp[i - h + 1][st][dr], i);
			}
		}
	}
/* 	for (int i = 0; i < int(txt[0].size()); ++i)
		cerr << dp[0][0][i];
	cerr << '\n';   
  	for (int i = 0; i < int(txt[0].size()); ++i)
		cerr << goRight[0][i] << '\t';
	cerr << '\n';                     */
	for (int i = 1; i < int(txt.size()); ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = 0; dr < int(txt[0].size()); ++dr) {
				getMax(dp[i][st][dr], dp[i - 1][st][dr]);
			}
		}
	}
 	
// 	for (int i = 0; i < int(txt.size()); ++i) {
//		cerr << txt[i] << '\n';
//	}
/*	for (int i = 0; i < int(txt.size()); ++i) {
		for (int j = 0; j < int(txt[0].size()); ++j) {
			cerr << goRight[i][j] << ' ';
		}
		cerr << '\n';
	}*/

	for (int i = 0; i < int(txt.size()); ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = 0; dr < int(txt[0].size()); ++dr) {
				if (goRight[i][st] + st - 1 >= dr) {
					dp[i][st][dr] = (dr - st - 1) * (dp[i][st][dr] - i - 1);
				} else {
					dp[i][st][dr] = 0;
 				}
			}
		}
	}
// 	for (int i = 0; i < int(txt[0].size()); ++i)
//		cerr << dp[0][2][i] << '\t';
//	cerr << '\n';   
}

int main() {	
	int n; in >> n;
	for (int i = 0; i < n; ++i) {
		string t; in >> t;
		txt.push_back(t);
	}
	solve();

	for (int i = 0; i < n; ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = 0; dr < int(txt[0].size()); ++dr) {
				down[i][st][dr] = dp[i][st][dr];
			}
		}
	}
	reverse(txt.begin(), txt.end());
/*	for (int i = 0; i < n; ++i) {
		cerr << txt[i] << '\n';
	}*/
	solve();
	for (int i = 0; i < n; ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = 0; dr < int(txt[0].size()); ++dr) {
				up[n - i - 1][st][dr] = dp[i][st][dr];
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int l = int(txt[0].size()) - 1; l; --l) {
			for (int st = 0; st + l < int(txt[0].size()); ++st) {
				int dr = st + l;
				getMax(down[i][st + 1][dr], down[i][st][dr]);
				getMax(down[i][st][dr - 1], down[i][st][dr]);
			}
		}
	}
	int mx = 0;
	for (int i = 0; i < n; ++i) {
		for (int st = 0; st < int(txt[0].size()); ++st) {
			for (int dr = st + 1; dr < int(txt[0].size()); ++dr) {
				getMax(mx, down[i][st][dr] * up[i][st][dr]);
			}
		}
	}
	out << mx << '\n';
	return 0;
}
