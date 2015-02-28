//Problem #B from Codeforces 239
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int Mod = 1000000007;

int rez[1005], p[1005];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> p[i];
	rez[1] = 0;
	rez[2] = 2;
	for (int i = 3; i <= n + 1; ++i) {
		rez[i] = (2 * rez[i - 1] - rez[p[i - 1]] + 2);
		if (rez[i] < 0)
			rez[i] += Mod;
		if (rez[i] >= Mod)
			rez[i] %= Mod;
	}
	cout << rez[n + 1] << '\n';
    return 0;
}

//Problem B from Codeforces Round 239
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
