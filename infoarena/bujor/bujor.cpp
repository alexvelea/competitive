//Problem bujor from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 205;
const double eps = 1.0e-7;

ifstream in("bujor.in");
ofstream out("bujor.out");

double gauss[kMaxN][kMaxN];
vector< pair< pair<int, int>, double > > changes;

double equal(double a, double b) {
	if (b - eps < a and a < b + eps)
		return true;
	return false;
}

double rez[kMaxN], P[kMaxN][kMaxN];

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				in >> gauss[i][j];
			}
		}
        
		changes.clear();

		for (int c = 1; c <= n; ++c) {
			for (int l = c; l <= n; ++l) {
				if (not equal(gauss[l][c], 0.0)) {	
					for (int x = 1; x <= n; ++x) {
						swap(gauss[c][x], gauss[l][x]);
					}
					for (auto &itr : changes) {
						if (itr.first.first == c or itr.first.first == l) {
							itr.first.first = l + c - itr.first.first;
						}
 						if (itr.first.second == c or itr.first.second == l) {
							itr.first.second = l + c - itr.first.second;
						}   					
					}

					break;
				}
			}
			for (int l = 1; l <= n; ++l) {
				if (l == c)
					continue;
				if (not equal(gauss[l][c], 0.0)) {
					double exp = - gauss[l][c] / gauss[c][c];
					changes.push_back(make_pair(make_pair(c, l), exp));
					for (int x = 1; x <= n; ++x) {
						gauss[l][x] += exp * gauss[c][x];
					}
				}
			}
		}

		for (int c = 1; c <= n; ++c) {
			for (int i = 1; i <= n; ++i)
				rez[i] = 0.0;
			rez[c] = 1.0;
			for (auto itr : changes) {
				int a = itr.first.first, b = itr.first.second;
				double exp = itr.second;
				rez[b] += exp * rez[a];
			}
			for (int i = 1; i <= n; ++i) {
				P[i][c] = rez[i] / gauss[i][i];
			}
		}
		for (int i = 1; i <= n; ++i, out << '\n') 
			for (int j = 1; j <= n; ++j) 
				out << fixed << setprecision(11) << P[i][j] << ' ';
	}
	return 0;
}
