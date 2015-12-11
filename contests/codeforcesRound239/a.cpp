//Problem #A from Codeforces 239
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

int main() {
 	int a, b;
	cin >> a >> b;
	a *= a;
	b *= b;
	for (int x = -1000; x <= 1000; ++x) {
		if (x * x > a)
			continue;
		int d = a - x * x;
		int y = 0.5 + sqrt(d);
		if (y * y != d)
			continue;
		if (y == 0 or x == 0)
			continue;
 		int x2 = y;
		int y2 = -x;
		int r = x2 * x2 + y2 * y2;
		x2 = floor(1.0 * x2 * sqrt(b / r) + 0.5);
		y2 = floor(1.0 * y2 * sqrt(b / r) + 0.5);
		cerr << x << '\t' << y << "\t\t" << x2 << '\t' << y2 << '\n';
		if ((x2 * x2 + y2 * y2) != b)
			continue;
		if (x2 == 0 or y2 == 0)
			continue;
		if (x == x2 or y == y2)
			continue;
		cout << "YES\n";
		cout << "0 0\n";
		cout << x << ' ' << y << '\n';
		cout << x2 << ' ' << y2 << '\n';
		return 0;
	}
 	for (int x = -1000; x <= 1000; ++x) {
		if (x * x > a)
			continue;
		int d = a - x * x;
		int y = 0.5 + sqrt(d);
		if (y * y != d)
			continue;
		if (y == 0 or x == 0)
			continue;
  		int x2 = -y;
		int y2 = -x;
		int r = x2 * x2 + y2 * y2;
		x2 = floor(1.0 * x2 * sqrt(b / r) + 0.5);
		y2 = floor(1.0 * y2 * sqrt(b / r) + 0.5);
		if ((x2 * x2 + y2 * y2) != b)
			continue;
		if (x2 == 0 or y2 == 0)
			continue;
		if (x == x2 or y == y2)
			continue;
		cout << "YES\n";
		cout << "0 0\n";
		cout << x << ' ' << y << '\n';
		cout << x2 << ' ' << y2 << '\n';
		return 0;
	}
	cout << "NO\n";
    return 0;
}

//Problem A from Codeforces Round 239
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
