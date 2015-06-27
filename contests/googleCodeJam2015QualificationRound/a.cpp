//Problem a from googleCodeJam2015QualificationRound
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream fin("a.in");
ofstream fout("a.out");


int main() {
	ios::sync_with_stdio(false);
	int t; fin >> t;
	for (int T = 1; T <= t; ++T) {
		int n; fin >> n;
		string txt; fin >> txt;
		int sum = 0;
		int mx = 0;
		for (int i = 0; i < int(txt.size()); ++i) {
			mx = max(mx, i - sum);
			sum += txt[i] - '0';
		}
		fout << "Case #" << T << ": " << mx << '\n';
	}
	return 0;
}
