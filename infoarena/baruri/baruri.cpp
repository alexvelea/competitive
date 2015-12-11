#include <fstream>
#include <iostream>
using namespace std;

ifstream in("baruri.in");
ofstream out("baruri.out");

const int kMaxN = 100005;

int aib[kMaxN];
int el[kMaxN];
int n;

int aib_query(int poz) {
	if (poz == 0)
		return 0;
	int rez = 0;
	while (poz) {
		rez += aib[poz];
		poz -= poz & (-poz);
	}
	return rez;
}

void aib_update(int poz, int val) {
	while (poz <= n) {
		aib[poz] += val;
		poz += poz & (-poz);
	}
}

int main() {
	int t;
	in >> t;
	while (t--) {
		in >> n;
		for (int i = 1; i <= n; ++i)
			aib[i] = 0;
		for (int i = 1; i <= n; ++i) {
			in >> el[i];
			aib_update(i, el[i]);
		}
		int m;
		in >> m;
		while (m--) {
			int t;
			in >> t;
			if (t == 0) {
				int b, d;
				in >> b >> d;
				int st = b - d - 1;
				if (st <= 0)
					st = 0;
				int dr = b + d;
				if (dr >= n)
					dr = n;
				int rez = aib_query(dr) - aib_query(st) - el[b];
				out << rez << '\n';
 			}
			if (t == 1) {
				int x, b;
				in >> x >> b;
				aib_update(b, +x);
				el[b] += x;
			}
			if (t == 2) {
				int x, b;
				in >> x >> b;
				aib_update(b, -x);
				el[b] -= x;
			}
			if (t == 3) {
 				int x, b1, b2;
				in >> x >> b1 >> b2;
				aib_update(b1, -x);
				el[b1] -= x;
				aib_update(b2, +x);
				el[b2] += x;
			}
		}
	}
	return 0;
}
