//Problem #B from Codeforces code_strike_2014_finals
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 100005;

bool good[kMaxN];
int type[kMaxN];

bool inside[kMaxN];
bool first[kMaxN];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		good[i] = true;
	for (int i = 1; i <= m; ++i) {
		int aux;
		char c;
		cin >> c >> aux;
		if (c == '+')
			type[i] = +aux;
		else
			type[i] = -aux;
 		if (not first[aux]) {
	    	if (c == '-') {
            	inside[aux] = true;
			}
			first[aux] = true;
		}
	}

	int nr_inside = 0;
	for (int i = 1; i <= n; ++i)
		nr_inside += inside[i];

 	for (int i = 1; i <= m; ++i) {
		if (type[i] < 0)
			nr_inside--;
		else
			nr_inside++;

		if (type[i] < 0 and nr_inside != 0) {
			good[-type[i]] = false;
		}

		if (type[i] < 0 and nr_inside == 0 and type[i + 1] != -type[i] and i != m)
			good[-type[i]] = false;

		if (type[i] > 0 and nr_inside != 1)
			good[type[i]] = 0;
		
		if (type[i] > 0 and nr_inside == 1 and type[i - 1] != -type[i] and i != 1)
			good[type[i]] = 0;
	}
	int k = 0;
	for (int i = 1; i <= n; ++i)
		k += good[i];
	cout << k << '\n';
	for (int i = 1; i <= n; ++i)
		if (good[i])
			cout << i << ' ';
    return 0;
}

