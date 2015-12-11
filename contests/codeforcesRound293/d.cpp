//Problem D from Codeforces Round 293
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

double dp[2005][2005];
double chx;

int main() {
	int n;
    cin >> n;
	cin >> chx;
	int T;
	cin >> T;
	dp[0][0] = 1.0;
	for (int t = 1; t <= T; ++t) {
		dp[t][0] = (1 - chx) * dp[t - 1][0];
		for (int p = 1; p <= n; ++p) {
			if (p == n) 
				dp[t][n] = dp[t - 1][n];
			else
				dp[t][p] = dp[t - 1][p] * (1 - chx);
			dp[t][p] += dp[t - 1][p - 1] * chx;
		}
	}

	double rez = 0.0;
	for (int p = 1; p <= n; ++p) {
		rez += 1.0 * p * dp[T][p];
	}
	cout << fixed << setprecision(11) << rez << '\n';
	return 0;
}
//Problem D from Codeforces Round 293
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

const int inf = 0x3f3f3f3f;

int main() {

return 0;
}
//Problem D from Codeforces Round 293
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

const int inf = 0x3f3f3f3f;

int main() {

return 0;
}
