#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("caraibe.in");
ofstream out("caraibe.out");

const int max_n = 65005;
const long long mx = 1LL * 100000 * 100000;
#define mp make_pair

int n, Nr[max_n], inside;

struct stare {
	vector < pair<long long, int> > st;
	void push (long long x) {
		st.push_back(mp(x,1));
	}
	long long make (int x) {
		long long rez = mx;
		vector < pair<long long,int> > nw;
		nw.push_back (mp(0,inside - x));
		int i = 0;
		while (x) {
			if (st[i].second > x) {
				nw.push_back (mp(st[i].first+1, x));
				x = 0;
			} else {
				nw.push_back (mp(st[i].first+1, st[i].second));
				x -= st[i].second;
			}
			rez -= 1LL * nw.back().first * nw.back().second;
			++i;
		}
		swap (nw, st);
		push(rez);
		return rez;
	}
} s;

int main() {
	in >> n;
 	for (int i = 1; i <= n-2; ++i)
		in >> Nr[i];
	s.push(0);
	long long x;
	x = s.make(0);
	inside = 2;
	for (int i = n-2; i; --i) {
		x = s.make(Nr[i]);
		inside ++;
	}
	out << x;
}
