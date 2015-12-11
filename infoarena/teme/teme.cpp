//Problem teme from Infoarena
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

ifstream fin("teme.in");
ofstream fout("teme.out");

vector<pair<int, int> > event;

int main() {
 	int t; fin >> t;
	while (t--) {
		event.clear();
		int n; fin >> n;
		while (n--) {
			int x, y; fin >> x >> y;
			event.push_back({y, x});
		}
		sort(event.begin(), event.end());
		int mx = 0, sum = 0;
		for (auto itr : event) {
			sum += itr.second;
//			cerr << sum << '\t' << itr.first << '\n';
			if (sum - itr.first > mx) {
				mx = sum - itr.first;
			}
		}
		fout << mx << '\n';

	}
	return 0;
}
