//Problem lesbulan from Infoarena
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

ifstream fin("lesbulan.in");
ofstream fout("lesbulan.out");

int main() {
	int t; fin >> t;
	while (t--) {
		int n, m; fin >> n >> m;
		while (m--) {
			int a, b; fin >> a >> b;
			vertex[a] |= (1 << b);
			vertex[b] |= (1 << a);
		}
	}
	return 0;
}
