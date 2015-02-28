//Problem #C from Codeforces zepto
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 1005;

int edge[kMaxN][kMaxN];

char el[kMaxN][11][11];
int rez[kMaxN][2];
int from[kMaxN];
int best[kMaxN];

bool Set[kMaxN];

int main() {
	int x, y, k, w;
	cin >> x >> y >> k >> w;
 	for (int i = 1; i <= k; ++i) {
		for (int X = 1; X <= x; ++X)
			for (int Y = 1; Y <= y; ++Y)
				cin >> el[i][X][Y];
	}

	for (int i = 1; i <= k; ++i) {
		edge[i][0] = edge[0][i] = x * y;
		for (int j = i + 1; j <= k; ++j) {
			int sum = 0;
			for (int X = 1; X <= x; ++X)
				for (int Y = 1; Y <= y; ++Y)
			   		if (el[i][X][Y] != el[j][X][Y])
						++sum;
			sum *= w;
 			edge[i][j] = edge[j][i] = sum;
		}
		best[i] = x * y;
		from[i] = 0;
	}
	
    int sum = 0;
	best[0] = 0;

    for (int i = 0; i <= k; ++i) {
		int mn = x * y + 1, poz = 0;
 		for (int j = 0; j <= k; ++j)
			if (best[j] < mn and not Set[j]) {
	        	mn = best[j];
				poz = j;
			}
	
		sum += best[poz];

		Set[poz] = true;
		rez[i][0] = poz;
		rez[i][1] = from[poz];

		for (int j = 0; j <= k; ++j)
			if (edge[poz][j] < best[j]) {
				best[j] = edge[poz][j];
				from[j] = poz;
			}
	}
	cout << sum << '\n';
	for (int i = 1; i <= k; ++i) {
		cout << rez[i][0] << ' ' << rez[i][1] << '\n';
	}
	return 0;
}

