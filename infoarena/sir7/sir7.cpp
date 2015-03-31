//Problem sir7 from Infoarena
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

ifstream in("sir7.in");
ofstream out("sir7.out");

int mid, dif, n;
int64 sMin, sMax;

bool solve(int dist, bool show = false) {
//	cerr << dist << '\n';
	int st, dr;
	if (mid - (dist / 2) <= 0) {
		st = 1;
	} else {
		st = mid - (dist) / 2;
	}

	dr = st + dist;
	int low = n, high = 0;
	int64 sum = 1LL * low * st;
	int64 rest = sMax - sum;
//	cerr << mid << '\t' << st << '\t' << dr << '\n';
//	cerr << rest << '\t' << dist << '\n';
	low = n;

	if (dist) 
		high = rest / dist;
	else
		high = 0;

	low -= high;
	rest -= 1LL * high * dist;
	low--;
//	cerr << low << '\t' << high << '\n';
	// avem low * st, rest + st, high * dr
	cerr << "????\t" << low << "@" << st << '\t' << rest << '\t' << high << "@" << dr << '\n';

	if (show) {
		out << rest + st << ' ';
		for (int i = 1; i <= low; ++i) {
			out << st << ' ';
		}
		for (int i = 1; i <= high; ++i) {
			out << dr << ' ';
		}
		out << '\n';
	}
		
	int64 final = 1LL * low * st * st + 1LL * (rest + st) * (rest + st) + 1LL * high * dr * dr;
	cerr << dist << '\t' << final << '\n';
	if (final >= sMin) {
		return true;
	} else {
		return false;
	}
}

bool solve2(int dist, bool show = false) {
	int64 bonus = 1LL * dist * n;
	int st = (sMax - bonus) / n;
	while (st * n + bonus < sMax) {
		++st;
	}
	st = max(st, 1);
	int64 final = 0;
	int high = 0, low = n;
	if (dist) {
		high = (sMax - st * n) / dist;
	}
	low -= high;
	low--;
	int rest = sMax - high * (st + dist) - low * st;
	cerr << low << "@" << st << '\t' << rest << '\t' << high << "@" << st + dist << '\n';
	final = 1LL * low * st * st + rest * rest + 1LL * high * (st + dist) * (st + dist);
	cerr << final << '\n';

	return final >= sMin;
}

int main() {
	int t; in >> t;
	while (t--) {
		in >> n >> sMax >> sMin;
		mid = sMax / n;
		dif = sMax - mid * n;

		for (int i = 0; i <= 10; ++i) {
			solve(i);
			solve2(i);
		}
		return 0;

		int rez = -1;
		int p = 30;
		for (; p >= 0; --p) {
			if (solve(rez + (1 << p))) {
				;
			} else {
				rez += (1 << p);
			}
		}
		rez++;
		solve(rez, true);
	}
	return 0;
}
