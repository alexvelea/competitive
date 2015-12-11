//Problem prietenie3 from Infoarena
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

ifstream fin("prietenie3.in");
ofstream fout("prietenie3.out");

int main() {
	int t; fin >> t;
	while (t--) {
		int n, m; fin >> n >> m;
		vector<pair<int, int> > event;
		event.reserve(n + m + 5);
		for (int i = 1; i <= n; ++i) {
			int x; fin >> x;
			event.push_back(make_pair(x, 0));
		}
		for (int i = 1; i <= m; ++i) {
			int x; fin >> x;
			event.push_back(make_pair(x, 1));
		}
		sort(event.begin(), event.end());
		vector<int64> rez(event.size(), 0);
		int nr;
		int64 r = 0;

		nr = 0;
		for (int i = 0; i + 1 < int(event.size()); ++i) {
			if (event[i].second == 0) {
				nr++;
			}
			r += 1LL * nr * (event[i + 1].first - event[i].first);
			rez[i + 1] += r;
		}
	   	nr = 0;
		r = 0;
		for (int i = int(event.size()) - 1; i > 0; --i) {
			if (event[i].second == 1) {
				nr++;
			}
			r += 1LL * nr * (event[i].first - event[i - 1].first);
			rez[i - 1] += r;
		}
   		int64 mn = 1LL * inf * inf;
		for (int i = 0; i < int(event.size()); ++i) {
			if (rez[i] < mn) {
				mn = rez[i];
			}
		}
		fout << mn << '\n';
	}
	return 0;
}
