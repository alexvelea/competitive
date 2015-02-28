//Problem D from Codeforces Round 291
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

vector<array<int, 5> > el;
deque<int> d[5];

array<int, 5> getRez(int &m) {
	array<int, 5> rez;
	for (int i = 0; i < m; ++i) {
		if (d[i].size())
			rez[i] = el[d[i].front()][i];
		else
			rez[i] = 0;
	}
	return rez;
}



int main() {
 	int n, m, k;          
    cin >> n >> m >> k;
	el.resize(n);
	cerr << el.size() << '\n';

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> el[i][j];
		}
	}
	
	int dr = 0;
	for (int i = 0; i < n; ++i) {
 		for (int j = 0; j < m; ++j) {
			if (d[j].size() and d[j].front() == i)
				d[j].pop_front();
		}
		// insert
	}
	return 0;
}
