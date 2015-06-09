//Problem b from googleCodeJam2015QualificationRound
//"We are drowning in information and starved for knowledge."
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

ifstream fin("b.in");
ofstream fout("b.out");

int main() {
	ios::sync_with_stdio(false);
	int t; fin >> t;
	for (int T = 1; T <= t; ++T) {
		int n; fin >> n;
		vector<int> el(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			fin >> el[i];
		}

        int mn = inf;

		for (int b = 1; b <= 1000; ++b) {
			int act = 0;
			for (int i = 1; i <= n; ++i) {
				act += (el[i] - 1) / b;
			}
			act += b;
			mn = min(mn, act);
		}

		fout << "Case #" << T << ": " << mn << '\n';
	}
	return 0;
}

