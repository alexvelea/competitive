//Problem suma5 from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("suma5.in");
ofstream out("suma5.out");

int init_val[kMaxN];

struct Aint {
	int st, dr;
	int64 sum, sum_s;
	int lazy;
    Aint *left, *right;

	Aint() {
		st = dr = 0;
		sum = sum_s = 0;
		lazy = 0;
		left = right = NULL;
	}

	Aint(int _st, int _dr) {
		st = _st;
		dr = _dr;
		lazy = 0;
		if (st == dr) {
			lazy = init_val[st];
			sum = 1LL * st * init_val[st];
			sum_s = init_val[st];
			return ;
		}
		int m = (st + dr) / 2;
		left = new Aint(st, m);
		right = new Aint(m + 1, dr);

		sum = left->sum + right->sum;
		sum_s = left->sum_s + right->sum_s;
	}

	void update_sum() {
		if (st == dr) {
			sum = lazy * st;
			sum_s = lazy;
			return ;
		}

		sum = left->sum + right->sum + 1LL * lazy * (1LL * dr * (dr + 1) / 2 - 1LL * (st - 1) * (st) / 2);
		sum_s = left->sum_s + right->sum_s + 1LL * lazy * (dr - st + 1);
	}
 	
    void split_lazy() {
    	if (lazy and st != dr) {
			left->lazy += lazy;
			left->update_sum();

			right->lazy += lazy;
			right->update_sum();

			lazy = 0;
		} 
	}

	void update(int c1, int c2, int v) {
 		if (dr < c1 or c2 < st)
			return ;
		
		if (c1 <= st and dr <= c2) {
			lazy += v;
			update_sum();
			return ;
		}

	 	split_lazy();  

		left->update(c1, c2, v);
		right->update(c1, c2, v);

		update_sum();
	}

	pair<int64, int64> query(int c2) {
 		if (c2 >= dr)
			return make_pair(sum, sum_s);
		split_lazy();
        int m = (st + dr) / 2;
		if (m + 1 <= c2) {
			pair<int64, int64> a, b;
			a = make_pair(left->sum, left->sum_s);
			b = right->query(c2);
			a.first += b.first;
			a.second += b.second;
			return a;
		} else
			return left->query(c2);
	}
} ;

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		in >> init_val[i];
	}
	Aint root(1, n);

	while (m--) {
		int t;
		in >> t;
		if (t == 0) {
			int x, y, z;
			in >> x >> y >> z;
			root.update(x, y, z);
		} else {
			int st, dr;
			in >> st >> dr;
			st--;
 			pair<int64, int64> b = root.query(dr);
			pair<int64, int64> a;
			if (st == 0)
				a = make_pair(0, 0);
			else
				a = root.query(st);

			out << b.first - a.first - 1LL * st * (b.second - a.second) << '\n';
		}
	}

	return 0;
}
