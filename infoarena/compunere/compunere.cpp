//Problem compunere from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

class Aint {
  public:
	int query(int st, int dr) {
		return aintQuery(1, 1, size, st, dr);
	}
	void update(int poz, int val) {
		aintUpdate(1, 1, size, poz, val);
	}
	Aint() {
		size = 0;
	}
	Aint(int _size) {
		size = _size;
		size++;
		el.resize(4 * size);
	}

  private:
	vector<int> el;
	int size;
	int aintQuery(int nod, int st, int dr, int c1, int c2) {
		if (dr < c1 or c2 < st) {
			return 0;
		}
		
		if (c1 <= st and dr <= c2) {
			return el[nod];
		}

		int m = (st + dr) / 2;
		return max(aintQuery(2 * nod, st, m, c1, c2), aintQuery(2 * nod + 1, m + 1, dr, c1, c2));
	}

	void aintUpdate(int nod, int st, int dr, int poz, int val) {
		if (el[nod] < val) {
			el[nod] = val;
		}

		if (st == dr) {
			return ;
		}

		int m = (st + dr) / 2;
		if (poz <= m) {
			aintUpdate(2 * nod, st, m, poz, val);
		} else {
			aintUpdate(2 * nod + 1, m + 1, dr, poz, val);
		}
	}
};

ifstream in("compunere.in");
ofstream out("compunere.out");

int a[kMaxN], b[kMaxN];

unordered_map<int, int> whereA, whereB;
int scmRight[kMaxN], ap[kMaxN];

int main() {
	int n, m; in >> n >> m;
	Aint aint(n);
	for (int i = 1; i <= n; ++i) {
   		in >> a[i];
		whereA[a[i]] = i;
	} 

	for (int i = 1; i <= m; ++i) {
		in >> b[i];
		whereB[b[i]] = i;
	}

	int mx = 0;

	for (int i = m; i; --i) {
 		int poz = whereA[b[i]];

		if (poz == 0) {
			continue;
		}

		int r = aint.query(poz, n);
		r++;

		if (r > mx) {
			mx = r;
		}
		
		ap[r]++;
		scmRight[i] = r;

		aint.update(poz, r);
	}

	int A = 1, B = 1;
	vector<int> final;

	ap[0] = inf;
	while (A <= n and B<= m) {
 		if (a[A] == b[B]) {
			final.push_back(a[A]);
			ap[scmRight[B]]--;
			scmRight[B] = 0;
			++A; ++B;   	
		} else {
			if (mx != 0 and ap[mx] == 1 and (scmRight[B] == mx or scmRight[whereB[a[A]]])) {
				if (scmRight[whereB[a[A]]] == mx) {
					final.push_back(b[B]);
					ap[scmRight[B]]--;
					scmRight[B] = 0;
					++B;
				} else {
					final.push_back(a[A]);
					ap[scmRight[whereB[a[A]]]]--;
					scmRight[whereB[a[A]]] = 0;
					++A;
				}
			} else {
				if (a[A] < b[B]) {
					final.push_back(a[A]);
					ap[scmRight[whereB[a[A]]]]--;
					scmRight[whereB[a[A]]] = 0;
					++A;
				} else {
					final.push_back(b[B]);
					ap[scmRight[B]]--;
					scmRight[B] = 0;
					++B;
				}
			}
		}

		if (ap[mx] == 0) {
			--mx;
		}
	}

	while (A <= n) {
		final.push_back(a[A]);
		++A;
	}

	while (B <= m) {
		final.push_back(b[B]);
		++B;
	}

	out << final.size() << '\n';
	for (auto itr : final) {
		out << itr << ' ';
	}
	in.close();
	out.close();
	return 0;
}
