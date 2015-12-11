#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 5005;

int out[kMaxN];
char el[kMaxN];
vector<int> ins[kMaxN];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> el;
 		for (int j = 0; j < m; ++j) {
			int st = j, ok = false;
			while (j < m and el[j] == '1') {
				ok = 1;
				++j;
			}
			if (ok) {
				ins[st + 1].push_back(j);
			}
		}
	}
	int rez = 0, inside = 0;
	for (int st = 1; st <= m; ++st) {
		// insert
		for (int i = 0; i < int(ins[st].size()); ++i) {
			out[ins[st][i]]++;
			inside++;
		}
		int act = inside;
		for (int dr = st; act and dr <= m; ++dr) {
			if ((dr - st + 1) * act >= rez)
				rez = (dr - st + 1) * act;
			act -= out[dr];
		}

		inside -= out[st];
	}
	cout << rez << '\n';
	return 0;
}
