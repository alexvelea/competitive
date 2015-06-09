//Problem celemaiapropiatepuncteManhatan from Infoarena
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

ifstream fin("celemaiapropiatepuncteManhatan.in");
ofstream fout("celemaiapropiatepuncteManhatan.out");

set<pair<int, int> > lower, upper;

int main() {
	fin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		fin >> x >> y;
		points.push_back(make_pair(x, y));
	}
	sort(points.begin(), points.end());
	for (auto itr : points) {
		
	}

	return 0;
}
