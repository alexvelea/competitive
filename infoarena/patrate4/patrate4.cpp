#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("patrate4.in");
ofstream out("patrate4.out");

struct Three {
	int a, b, c;
	Three(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
};

vector<Three> rez;

int n, k;

int el[1050][1050];

void solve(int x, int y, int l) {
	int inside = el[x + l - 1][y + l - 1] + el[x - 1][y - 1] - el[x - 1][y + l - 1] - el[x + l - 1][y - 1];
	if (inside == 0)
		return ;
	int s = l * l;
	if ((int((s + k - 1)  / k) <= inside) and (inside < (int(4 * s + k - 1) / k))) {
		rez.push_back(Three(x, y, l));
	} else {
		solve(x, y, l / 2);
		solve(x + l / 2, y, l / 2);
		solve(x + l / 2, y + l / 2, l / 2);
		solve(x, y + l / 2, l / 2);
	}
}

int main() {
	in >> n >> k;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		in >> x >> y;
		el[x][y] = 1;
	}
	
	for (int i = 1; i < 1050; ++i)
		for (int j = 1; j < 1050; ++j)
			el[i][j] += el[i - 1][j] + el[i][j - 1] - el[i - 1][j - 1];
    
    solve(1, 1, 1024);
	out << rez.size() << '\n';
	for (int i = 0; i < int(rez.size()); ++i)
		out << rez[i].a << ' ' << rez[i].b << ' ' << rez[i].c << '\n';
	return 0;
}
