//Problem #C from Codeforces 233
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int rez[kMaxN];

int r = 0;

struct Edge{
	int a, b, c;
	Edge(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
} edge[kMaxN];

void solve(int max, int over) {
	edge[++nr_e] = Edge(1, 2, 1);
	edge[++nr_e] = Edge(2, 3, 1);
	rez[1] = over + 2;
	rez[4] = over + 1;
	int sum = 2;
	sum += 2 * (over + 1);
	edge[++nr_e] = Edge(3, 4, 2 * (over + 1));
	edge[++nr_e] = Edge(4, 5, 1);
	for (int i = 4; i <= max; ++i) {
		int el = sum - rez[1] - rez[i];
		if (el > 100000) {
			return;
		}
		if (el <= 0) {
			cout <<"Nu e ok\n";
			return ;
		}
		rez[i + 1] = el + over;
		sum += el;
		edge[++nr_e] = Edge(i + 1, i + 2, el);
	}
}

int main() {
	int n, i = 0, dr;
	cin >> n;
	dr = n;
	n--;
	for (; n > 0; ) {
		solve(n, i);
		++i;
		int st = dr - nr_e;

		for (int j = 1; j <= nr_e; ++j) {
			int a = edge[j].a;
			int b = edge[j].b;
			if (a != 1)
				a += st - 1;
			b += st - 1;
		}
	
		nr_e = 0;
	}
    return 0;
}

