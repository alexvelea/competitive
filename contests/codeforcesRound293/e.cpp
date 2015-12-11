//Problem E from Codeforces Round 293
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

int el[100005];

int main() {
	ios::sync_with_stdio(false);
	int n, k;
    cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		string e;
		cin >> e;
		if (e == "?")
			el[i] = +inf - 1;
		else {
			el[i] = atoi(e.c_str());
		}
	}

    bool ok = true;

	for (int i = 1; i <= k; ++i) {
		vector<int> E(n / k + 3);
		int K = 1;
        E[0] = -inf;
		for (int poz = i; poz <= n; poz += k) {
			E[K++] = el[poz];
		}
		E[K++] = +inf;
		E.resize(K);
		int st = 0, dr = 0;
		int empty = 0;
//		for (auto itr : E) {
//			cout << itr << '\t';
//		}
//		cout << '\n';
		for (auto itr : E) {
			if (itr == +inf - 1) {
				// prost
                ++empty;
			} else {
				if (E[dr] - E[st] > empty or st == dr) {
					if (empty) {
						if (E[st] >= 0) {
							for (int j = st + 1; j < dr; ++j) {
								el[(j - 1) * k + i] = E[st] + j - st;
							}
						} else if (E[dr] <= 0) {
							int val = E[dr] - 1;
							for (int j = dr - 1; j > st; --j, --val) {
								el[(j - 1) * k + i] = val;
							}
						} else {
							// cazul cu 0
							int c2 = empty / 2, c1 = 0;
							if (c2 > E[dr]) {
								c2 = E[dr];
							}
							c1 = c2 - empty + 1;
							if (c1 < E[st]) {
								c2 += (E[st] - c1);
								c1 = E[st];
							}
							for (int j = st + 1; j < dr; ++j, ++c1) {
								el[(j - 1) * k + i] = c1;
							}
						}
					}
					empty = 0;
				} else {
					ok = false;
				}
				st = dr;
			}

			++dr;
		}
	}
	if (ok == false) {
        cout << "Incorrect sequence";
		return 0;
	}

	for (int i = 1; i <= n; ++i) {
		if (i + k <= n)
			assert(el[i] < el[i + k]);
		cout << el[i] << ' ';
	}
	cout << '\n';
	return 0;
}
//Problem E from Codeforces Round 293
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
