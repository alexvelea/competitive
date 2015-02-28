#include <iostream>
#include <fstream>
using namespace std;

const int kMaxN = 10005;

//ifstream in("library.in");
//ofstream out("library.out");

int aib[kMaxN][1025];
int n, el[kMaxN];

void aib_update(int x, int Y, int val) {
	int y;
	while (x <= n) {
		y = Y;
		while (y < 1025) {
			aib[x][y] += val;
			y += y & (-y);
		}
		x += x & (-x);
	}
	return ;
}

int aib_get_fixed_y(int x, int y) {
	int rez = 0;
	while (x) {
		rez += aib[x][y];
		x -= x & (-x);
	}
	return rez;
}


int aib_special_query(int st, int dr, int k) {
	int rez = 0, p;
	for (p = 1 << 10; p; p >>= 1) {
    	int val = aib_get_fixed_y(dr, rez + p);
		val -= aib_get_fixed_y(st, rez + p);
		if (val < k) {
			rez += p;
			k -= val;
		}
	}
	return rez + 1;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
            cin >> el[i];
			aib_update(i, el[i], +1);
		}
		int q;
 		cin >> q;
 		while (q--) {
			int t;
			cin >> t;
			if (t == 0) {
				int st, dr, k;
				cin >> st >> dr >> k;
				cout << aib_special_query(st - 1, dr, k) << '\n';
			} else {
				int x, e;
				cin >> x >> e;
				aib_update(x, el[x], -1);
				el[x] = e;
				aib_update(x, el[x], +1);
			}
		}
		for (int i = 1; i <= n; ++i)
			aib_update(i, el[i], -1);
	}
	return 0;
}
