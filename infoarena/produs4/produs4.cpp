//Problem produs4 from Infoarena
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

ifstream fin("produs4.in");
ofstream fout("produs4.out");

int main() {
	int t; fin >> t;
	while (t--) {
		int n; 	fin >> n;
		vector<int> u;
		while (n--) {
			int x; fin >> x;
			u.push_back(x);
		}
		sort(u.begin(), u.end());
		n = u.size();
		int64 a = 1LL * u[0] * u[1] * u[n - 1];
		int64 b = 1LL * u[n - 1] * u[n - 2] * u[n - 3];
		fout << max(a, b) << '\n';
	}
	return 0;
}
