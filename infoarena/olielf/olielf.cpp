//Problem olielf from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("olielf.in");
ofstream out("olielf.out");

pair<int, int> coord[12345];

int main() {
	int n = 10;
	int m = 20;
	srand(time(NULL));
	for (int i = 1; i <= m; ++i) {
		coord[i].first = rand() % n;
		coord[i].second = rand() % n;
	}

	int mn = inf;

	for (int i = -n; i < 2 * n; ++i) 
		for (int j = -n; j < 2 * n; ++j) {
			int d = 0;
			for (int l = 1; l <= m; ++l) {
				d = max(d, abs(i - coord[l].first) + abs(j - coord[l].second));
			}
			if (d < mn)
				mn = d;
		}

 	for (int i = -n; i < 2 * n; ++i, cout << '\n' ) 
		for (int j = -n; j < 2 * n; ++j) {
 			int d = 0;
			for (int l = 1; l <= m; ++l) {
				d = max(d, abs(i - coord[l].first) + abs(j - coord[l].second));
			}
			if (d == mn)
				cout << "*";
			else
				cout << " ";
		}       	
	return 0;
}
