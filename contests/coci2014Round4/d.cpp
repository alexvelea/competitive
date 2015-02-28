//Problem D from Codeforces Round coci.2014.round4
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005;

struct Pipe {
	int a, b, x, t;
	int oth(int _nod) {
		return a + b - _nod;
	}
} pipe[kMaxN];

bool viz[kMaxN];
double minWater[kMaxN];
vector<int> edge[kMaxN];

void solve(int nod) {
	viz[nod] = true;
	for (int itr : edge[nod]) {
		int oth = pipe[itr].oth(nod);
		if (viz[oth])
			continue;
		solve(oth);
		double a = minWater[oth];
		if (pipe[itr].t)
			a = sqrt(a);
		a /= (pipe[itr].x / 100.0);
		if (a > minWater[nod])
			minWater[nod] = a;
	}

	return ;
}

int main() {
	int n;
    cin >> n;
	for (int i = 1; i < n; ++i) {
		cin >> pipe[i].a >> pipe[i].b >> pipe[i].x >> pipe[i].t;
		edge[pipe[i].a].push_back(i);
		edge[pipe[i].b].push_back(i);
	}

	for (int i = 1; i <= n; ++i)
    	cin >> minWater[i];

	solve(1);
	cout << fixed << setprecision(9) << minWater[1] << '\n';
	return 0;
}
