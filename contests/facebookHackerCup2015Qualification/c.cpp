//Problem C from Codeforces Round facebookHackerCup2015Qualification
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

int main() {
	int t;
    in >> t;
	for (int T = 1; T <= t; ++T) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				for (int d = 0; d < 4; ++d) {
		 			ok[d][i][j] = true;   		
				}
			}
		}

		for (int i = 1; i <= n; ++i) {
			cin >> el[i];
			el[i] = '#' + el[i];
		}

 		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (el[i][j] == '.' or el[i][j] == 'S' or el[i][j] == 'G')
					continue;
				if (el[i][j] == '#') {
					for (int d = 0; d < 4; ++d) {
						ok[d][i][j] = 0;
					}
				} else {
					int initD = 0;
					if (el[i][j] == '^') {
						initD = 0;
					}
					if (el[i][j] == '>') {
						initD = 1;
					}
					if (el[i][j] == 'v') {
						initD = 2;
					}
					if (el[i][j] == '<') {
						initD = 3;
					}

					for (int d = 0; d < 4; d++, initD++) {
						int x = i + dx[initD], y = j + dy[initD];
						while (el[x][y] == '.' or el[x][y] == 'S' or el[x][y] == 'G') {
							ok[d][x][y] = false;
							x += dx[initD];
							y += dy[initD];
						}
					}
				}
			}
		}
	}
	return 0;
}
