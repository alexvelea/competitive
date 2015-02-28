//Problem seerc2014pumpkin from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
//#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 60005, kMaxS = 250;

vector<int> el;

ifstream cin("date.in");
ofstream cout("date.out");

int nr[kMaxN], all[kMaxN / kMaxS + 5];
bool ok[kMaxN];
//unordered_map<int, int> ap[kMaxN / kMaxS + 5];
int ap[kMaxN / kMaxS + 5][2 * kMaxN + 5];


int main() {
	int n, k;
	while (cin >> n >> k) {
		if (n == 0 and k == 0) {
			continue;
		}

 		el.clear();
		for (int i = 1; i <= n; ++i) {
			cin >> nr[i];
			ok[i] = true;
			el.push_back(nr[i]);
		}

		sort(el.begin(), el.end());
		int median = el[n / 2];
		int bonus = - k + median;
		for (int i = 1; i <= n; ++i) {
			nr[i] += k - median;
		}
/*		for (int i = 1; i <= n; ++i) {
			if (nr[i] >= 0 and nr[i] <= 2 * k) {
				;
			} else {
				ok[i] = false;
			}
		}*/
 		
		int under = 0, target = (n + 1) / 2;
		for (int i = 1; i <= n; ++i) {
			if (nr[i] <= median) {
				++under;
			}
		}

		for (int i = 1; i <= n; ++i) {
			if (nr[i] >= 0 and nr[i] < 2 * kMaxN) {
				ap[i / kMaxS][nr[i]]++;
			}
		}

/*		cout << "!!!!\n";
		for (int i = 1; i <= n; ++i)
			cout << nr[i] << '\t';
		cout << '\n';
		cout << under << '\t' << target << '\t' << median << '\n';
		for (int i = 1; i <= n; ++i)
			cout << all[i] << '\t';
		cout << "~~~\n"; */

		while (k--) {
			int st, dr;
			cin >> st >> dr;
 			for (int i = 0; i * kMaxS <= n; ++i) {
		  		int c1 = i * kMaxS;
				int c2 = (i + 1) * kMaxS - 1;
				if (st <= c1 and c2 <= dr) {
					under -= ap[i][median - all[i]];
					all[i]++;
				} else {
					c1 = max(c1, st);
					c2 = min(c2, dr);
					for (; c1 <= c2; ++c1) {
						if (nr[c1] >= 0 and nr[c1] < 2 * kMaxN) {
							if (nr[c1] + all[i] == median) {
								--under;
							}
 							ap[i][nr[c1]]--;
							nr[c1]++;
  							ap[i][nr[c1]]++;   						
						}
					}
				}
			}
			while (under < target) {
				median++;
				for (int i = 0; i * kMaxS <= n; ++i) {
					under += ap[i][median - all[i]];
				}
			}
			cout << median + bonus << '\n';
		}

		for (int i = 0; i * kMaxS <= n; ++i) {
			all[i] = 0;
			for (int j = 0; j < 2 * kMaxN; ++j)
				ap[i][j] = 0;
		}

	}
	return 0;
}
