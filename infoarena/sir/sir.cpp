#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("sir.in");
ofstream out("sir.out");

const int kMaxN = 100005;

int n, inside;
int aib[kMaxN], el[kMaxN];
vector<pair<int, int> > query;

void aib_update(int ind, int val) {
	while (ind <= n) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
}

int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}
int aib_search(int val) {
	if (val == -1)
		return -1;
	int p = 1, rez = 0;
	while (p < n)
		p *= 2;
	for (; p; p /= 2)
		if (rez + p <= n)
			if (aib[rez + p] <= val) {
				val -= aib[p];
				rez += p;
			}
	return rez;
}

int main() {
	int x, y, z;
	in >> n >> y >> x >> z;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
        query.push_back(make_pair(el[i], +i));
		query.push_back(make_pair(el[i] + z + 1, -i));
	}
	sort (query.begin(), query.end());
	for (int i = 1; i <= n; ++i)
		aib_update(i, +1);

	int rez = 0, c1;

	for (int st = 0; st < int(query.size()); ) {
		int dr = st;
    	while (dr < int(query.size()) and query[st].first == query[dr].first) {
			int op = query[dr].second;
			if (op > 0)
				aib_update(op, -1);
			else
				aib_update(-op, +1);
			++dr;
		}
		for (; st < dr; ++st) {
			int op = query[st].second;
			if (op > 0) {
				int c, a, b;
				c = aib_query(op);
				b = aib_search(c);
				a = aib_search(c - 1) + 2;
				if (b - a + 1 > x)
					a += (b - a + 1) - x;
				if (b - a + 1 > rez) {
					rez = b - a + 1;
					c1 = a;
				}
				if (b - a + 1 == rez and a > c1)
					c1 = a;
			}
		}
	}
	if (rez < y)
		out << -1;
	else
		out << rez << ' ' << c1 << ' ' << c1 + rez - 1 << '\n';
    return 0;
}
