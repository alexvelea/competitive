#include <cassert>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define cin fin
#define cout fout

int main() {
	int nr_of_testcases; cin >> nr_of_testcases;
	for (int test = 1; test <= nr_of_testcases; test += 1) {
		int n, k; cin >> n >> k;
		int answer = +inf;

		vector<vector<int> > dp(n + 1);
		for (int i = 0; i <= n; i += 1) {
			dp[i] = vector<int>(k + 1, +inf);
		}

		dp[0][0] = 0;

		vector<string> txt = {""};

		for (int i = 0; i < n; i += 1) {
			string _txt; cin >> _txt;
			txt.push_back(_txt);
		}

		sort(txt.begin(), txt.end());

		txt.resize(unique(txt.begin(), txt.end()) - txt.begin());

		assert (int(txt.size()) - 1 == n);

		for (int i = 1; i <= n; i += 1) {
			int lcp = 0;
			for (int j = 0; j < i; j += 1) {
				while (lcp < int(txt[j].size()) and txt[j][lcp] == txt[i][lcp]) {
					lcp += 1;
				}

				// cerr << i << '\t' << j << '\t' << lcp << '\n';

				// for (int len = 1; len <= k; len += 1) {
				// 	cerr << i << '\t' << dp[i][len] << '\n';
				// }
				// cerr << '\n';

				for (int len = 1; len <= k; len += 1) {
					dp[i][len] = min(dp[i][len], 1 + int(txt[i].size() + txt[j].size()) - 2 * lcp + dp[j][len - 1]);
				}
			}

			answer = min(answer, dp[i][k] + int(txt[i].size()));
		}

		cout << "Case #" << test << ": " << answer << '\n';
	}	
	return 0;
}
