//Problem #D from Codeforces 229
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define mp make_pair

const int inf = 0x3f3f3f3f;

vector<pair<int, pair<int, int> > > el;

int main() {
	int n, m, k;
	cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			el.push_back(mp(i + j - 1, mp(i, j)));
	sort(el.begin(), el.end());
	int rez = 0;
 	for (int i = 0; i < k; ++i)
		rez += el[i].fi;

	cout << rez << '\n';
	for (int i = k - 1; i >= 0; --i) {
		int x = 1, y = 1;
		int X = el[i].se.fi;
		int Y = el[i].se.se;
 		while (x < X or y < Y) {
			cout << "(" << x << "," << y << ") ";
			if (x < X) {
				++x;
			} else {
				++y;
			}
		}
		cout << "(" << x << "," << y << ")\n";
	}	
	return 0;
}

