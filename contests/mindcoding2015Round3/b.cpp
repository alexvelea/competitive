//Problem b from mingcoding2015Round3
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

char lin[1005][1005], col[1005][1005], up[1005][1005];
int rez[1005][1005];

int main() {
	ios::sync_with_stdio(false);
 	int n, m, h; cin >> n >> m >> h;
	
	for (int i = 0; i < n; ++i) {
		cin >> up[i];
	}
	
	for (int i = 0; i < h; ++i) {
		cin >> lin[i];
	}
	
	for (int i = 0; i < h; ++i) {
		cin >> col[i];
	}

    for (int j = m - 1, i = 0; j >= 0; --j, ++i) {
		int H = h, itr = 0;
		while (H and lin[itr][i] == '.') {
			--H;
			++itr;
		}
		for (int l = 0; l < n; ++l) {
			if (up[l][i] == '#') {
				rez[l][i] = H;
			}
		}
	}

     for (int j = n - 1, i = 0; j >= 0; --j, ++i) {
		int H = h, itr = 0;
		while (H and col[itr][i] == '.') {
			--H;
			++itr;
		}
		
		for (int c = 0; c < m; ++c) {
			if (up[j][c] == '#') {
				rez[j][c] = min(H, rez[j][c]);
			}
		}
	}   

  	for (int i = 0; i < n; ++i, cout << '\n')
		for (int j = 0; j < m; ++j) {
			if (rez[i][j] == 0)
				cout << '.';
			else 
				cout << rez[i][j];
		}

	return 0;
}
