//Problem #D from Codeforces rocket
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 0
#else
#define DEBUG 0
#endif

#define fi first
#define se second

const int inf = 0x3f3f3f3f, kMaxN = 50005;

struct Line{
	int x, y, d;
	int t;
	Line() {
		x = y = d = 0;
		t = 0;
	}
	Line(int _x, int _y, int _d, int _t) {
    	x = _x;
		y = _y;
		d = _d;
		t = _t;
	}
	bool operator < (const Line &rhs) const {
		if (x == rhs.x) {
			return t > rhs.t;
		}
		return x < rhs.x;
	}
};

vector<int> uniq;
vector<Line> task, col;

int n, m;
int x[kMaxN], y[kMaxN], d[kMaxN];

int aib[kMaxN];
int aib_query(int poz) {
	int rez = 0;
	while (poz) {
		rez += aib[poz];
		poz -= poz & (-poz);
	}
	return rez;
}
void aib_update(int poz, int val) {
	while (poz < kMaxN) {
		aib[poz] += val;
		poz += poz & (-poz);
	}
}


int bs(int val) {
	int rez = 0;
	int p = 1;
	while (p < int(uniq.size()))
		p <<= 1;
	for (; p; p >>= 1)
		if (rez + p < int(uniq.size()))
			if (uniq[p + rez] <= val)
				rez += p;
	return rez;
}

bool ok(int D) {
	task.clear();
    for (int i = 0; i < kMaxN; ++i)
		aib[i] = 0;

	for (int i = 0; i < n; ++i)
		if (D * 2 <= col[i].d)
	 		task.push_back(col[i]);
	for (int i = 1; i <= m; ++i) {
    	if (D * 2 <= d[i]) {
	    	task.push_back(Line(x[i] + D, y[i], 0, +1));
			task.push_back(Line(x[i] + d[i] - D, y[i], 0, -1));
		}
	}
	sort(task.begin(), task.end());
	if (DEBUG)
		cerr << '\n';
	for (int i = 0; i < int(task.size()); ++i) {
    	Line act = task[i];
		if (act.t == 0) {                      
			if (DEBUG)
				cerr << act.x << "\t" << D << '\n';
			int st = act.y + D;
			int dr = act.y + act.d - D;
			int c_st = bs(st);
			int c_dr = bs(dr);
			if (uniq[c_st] == st)
				--c_st;
			if (aib_query(c_st) != aib_query(c_dr))
				return true;
		} else {
			int poz = bs(act.y);
			if (DEBUG) {
				cerr << "Update\t" << act.x << '\t' << poz << '\t' << act.t << '\n';
			}
			aib_update(poz, act.t);
		}
	}
	return false;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x, y, d;
		cin >> x >> y >> d;
		col.push_back(Line(x, y, d, 0));
	}
	for (int i = 1; i <= m; ++i) {
		cin >> x[i] >> y[i] >> d[i];
		uniq.push_back(y[i]);
	}
	uniq.push_back(- inf * inf);
	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
    int rez = 0;
	int p = 1 << 29;
	for (; p; p >>= 1) 
		if (ok(rez + p))
			rez += p;
	cout << rez << '\n';
	return 0;
}

