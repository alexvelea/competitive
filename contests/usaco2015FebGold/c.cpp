//Problem C from Codeforces Round usaco2015FebGold
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ifstream in("fencing.in");
ofstream out("fencing.out");

#define int64 long long

const int inf = 0x3f3f3f3f;
vector<pair<int, int> > coords;

int main() {
	int n, m;
    in >> n >> m;
	while (n--) {
		int x, y;
		in >> x >> y;
		coords.push_back(make_pair(x, y));
	}
	while (m--) {
		int t;
		in >> t;
		if (t == 1) {
			int x, y;
			in >> x >> y;
			coords.push_back(make_pair(x, y));
		} else {
			int a, b;
			int64 c;
			in >> a >> b >> c;
			c *= -1;
			bool ok = true;
			int lastDir = -1, dir = -1;
			for (auto itr : coords) {
				if (b == 0) {
					if (1LL * itr.first * a == c)
						ok = false;
					if (1LL * itr.first * a < c)
						dir = 0;
					else
						dir = 1;
				} else {
					if (-1LL * b * itr.second == 1LL * a * itr.first + c)
						ok = false;
 					if (-1LL * b * itr.second < 1LL * a * itr.first + c)
						dir = 0;
					else
						dir = 1;
//					cerr << itr.first << '\t' << itr.second << '\t' << b * itr.second << '\t' << a * itr.first + c << '\n';
//					cerr << dir << '\n';
				}
				if (lastDir != -1 and dir != lastDir)
					ok = false;
				lastDir = dir;
				if (ok == false)
					break;
			}
			if (ok) {
				out << "YES\n";
			} else {
				out << "NO\n";
			}
		}
		
	}
	return 0;
}  	
