#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

const int inf = 0x3f3f3f3f;

int el[100005];

int main() {
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		string e;
		cin >> e;
		if (e == "?") {
			el[i] = 2 * inf;
		} else {
			el[i] = atoi(e.c_str());
		}
	}

	for (int i = 0; i < k; ++i) {
		int st = i;
		while (st < n) {
			int dr = st + k;
			while (dr < n and el[dr] == 2 * inf) {
				dr += k;
			}
 			int q = (dr - st) / k - 1;
 			if (el[st] == 2 * inf) {
				++q;
			}
			int c1 = el[st], c2;
			if (c1 == 2 * inf) {
				c1 = -inf;
			}

			if (dr >= n) {
				c2 = inf;
			} else {
				c2 = el[dr];
			}
//			cerr << st << '\t' << dr << '\n';
//			cerr << c1 << '\t' << c2 << '\n';
//			cerr << "\n\n";
			if (c2 - c1 > q) {
				;
			} else {
				cout << "Incorrect sequence";
				return 0;
			}
			
			if (c2 <= 0) {
				c1 = c2 - q;
			} else if (c1 > 0) {
				c1++;
			} else {
				c2 = min(c2, q / 2);
				if (c1 > c2 - q + 1) {
					c2 = c1 + q - 1;
				} else {
					c1 = c2 - q + 1;
				}
			}

			if (el[st] != 2 * inf) 
				st += k;
			for (; st != dr; st += k) {
				el[st] = c1;
				c1++;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << el[i] << ' ';
	}
}
