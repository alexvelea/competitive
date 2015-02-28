//Problem D from Codeforces Round good.bye.2014
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int under[kMaxN], a[kMaxN], b[kMaxN], cost[kMaxN];
bool viz[kMaxN];

long double expected[kMaxN];

vector<int> edge[kMaxN];

int df(int nod) {
	int rez = 0;
	viz[nod] = true;
	for (int itr : edge[nod]) {
		int oth = a[itr] + b[itr] - nod;
		if (not viz[oth]) {
			int aux = df(oth);
			rez += aux;
			under[itr] += aux;
		}	
	}
	return rez + 1;
}

int A[kMaxN], B[kMaxN];

int main() {
	int n;
    cin >> n;
	for (int i = 1; i < n; ++i) {
		cin >> a[i] >> b[i];
		cin >> cost[i];
		edge[a[i]].push_back(i);
		edge[b[i]].push_back(i);
	}
	df(1);
 	
	for (int i = 1; i <= n; ++i) {
		expected[i] = (1.0 * i * (n - i) * (n - i - 1) / 2.0 + 1.0 * i * (i - 1) / 2.0 * (n - i)) / (1.0 * n * (n - 1.0) * (n - 2.0) / 6.0);
	}
	
	long double rez = 0;
	int m; cin >> m;
    for (int i = 1; i <= m; ++i)
		cin >> A[i] >> B[i];

	for (int i = 1; i < n; ++i) {
		rez += 1.0 * cost[i] * expected[under[i]];
	}

	for (int i = 1; i <= m; ++i) {
		rez -= 1.0 * cost[A[i]] * expected[under[A[i]]];
		cost[A[i]] = B[i];
 		rez += 1.0 * cost[A[i]] * expected[under[A[i]]];   	
		cout << fixed << setprecision(12) << 2.0 * rez << '\n';
	}
	return 0;
}
