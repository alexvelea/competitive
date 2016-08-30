#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include <ctime>
#include <cstdlib>
using namespace std;

#define int64 long long

ifstream fin("granita.in");
ofstream fout("granita.out");

const int kMaxN = 2e4 + 5;

pair<int, int> el[kMaxN];

int main() {
	int n; fin >> n;
	for (int i = 1; i <= n; i += 1) {
		int x, y; fin >> x >> y;
		el[i] = {x, -y};
	}
	sort(el + 1, el + n + 1);
	int mxDr = (-el[1].second) - 1;
	int rez = 0;
	for (int i = 1; i <= n; i += 1) {
		if (-el[i].second <= mxDr) {
			rez += 1;
		}
		mxDr = max(mxDr, -el[i].second);
	}
	fout << rez << '\n';
	return 0;
}