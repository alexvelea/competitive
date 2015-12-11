//Problem a from codeforcesLooksery
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

string txt[105];

int main() {
	ios::sync_with_stdio(false);
 	int n, m; cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> txt[i];
	}
	int rez = 0;
	for (int i = 0; i + 1 < n; ++i) {
		for (int j = 0; j + 1 < m; ++j) {
	 		string t;
			t += txt[i][j];
			t += txt[i + 1][j];
			t += txt[i][j + 1];
			t += txt[i + 1][j + 1];
			sort(t.begin(), t.end());
			if (t == "acef") {
				++rez;
			}
		}
	}
	cout << rez << '\n';
	return 0;
}
