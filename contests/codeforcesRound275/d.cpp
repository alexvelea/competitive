//Problem D from Codeforces Round 2775
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

vector<int> edge[3005];
int rez[3005];

int main() {
	int n, m;
	cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
	}                 
	int64 R = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			rez[j] = 0;
		for (int it : edge[i])
			for (int it2 : edge[it]) {
				if (it2 != i) {
					R += rez[it2];
					rez[it2]++;
				}
			}
	}
	cout << R << '\n';
	return 0;
}
