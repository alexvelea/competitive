#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("rev.in");
ofstream out("rev.out");

const int kMaxN = 505; // sqrt(n) * 1.5

int kMaxL;
int st, dr, k;

struct line{
 	vector<int> el;
	bool inverse;
	line() {
		inverse = false;
	}

	void Reverse() {
		if (inverse) {
			inverse = 0;
			reverse(el.begin(), el.end());
		}
	}

	line(int n) {
		inverse = false;
		for (int i = 1; i <= n; ++i)
			el.push_back(i);
	}
	line(vector<line> &x) {
		int n = x.size();
		inverse = false;
		for (int i = 0; i < n; ++i) {
			x[i].Reverse();
			for (int j = 0; j < x[i].el.size(); ++j)
				el.push_back(x[i].el[j]);
		}
	}
	line split(int ind) {
		line rez;
        if (inverse == 0) {
			for (int i = ind; i < int(el.size()); ++i) {
				rez.el.push_back(el[i]);
			}
			el.erase(el.begin() + ind, el.end());
			return rez;
		} else {
			--ind;
			ind = el.size() - ind - 1;
			rez.inverse = true;
			for (int i = 0; i < ind; ++i)
				rez.el.push_back(el[i]);
 			el.erase(el.begin(), el.begin() + ind);
			return rez;
		}
	}
};

vector<line> L;
 
void DEBUG() {
	for (int i = 0; i < int(L.size()); ++i) {
		L[i].Reverse();
		for (int j = 0; j < int(L[i].el.size()); ++j)
			cerr << L[i].el[j] << ' ';
		cerr << " | \t";
	}
	cerr << '\n';
}

int here[kMaxN], where[kMaxN], target[kMaxN];

void solve() {
	st--;

//	DEBUG();

	int i = 0;
	int cSt, cDr;
	while (st >= 0) {
		int n = L[i].el.size();
		if (st <= n and dr > n) {
			L.push_back(L[i].split(st));
			cSt = i;

			st = -1;
			dr -= n;
			++i;
			break;
		} else {
			if (st <= n and dr <= n) {
				cSt = i;
				cDr = i + 1;
				L.push_back(L[i].split(st));
				dr -= L[i].el.size();
				L.push_back(L.back().split(dr));
				L.back().inverse ^= 1;
				swap(L.back(), L[L.size() - 2]);
				st = -1;
				dr = 0;
			}
		}
		st -= n;
		dr -= n;
		++i;
	}

	while (dr >= 0) {
		int n = L[i].el.size();
		if (dr <= n) {
			L.push_back(L[i].split(dr));
			swap(L[i], L.back());
			cDr = i;
			break;
		}
		dr -= n;
		++i;
	}
	int n = L.size();
	for (int i = 0; i < n; ++i) {
		here[i] = i;
		where[i] = i;
	}

// 	DEBUG();

	for (int i = 0; i <= cSt; ++i)
		target[i] = i;
	for (int i = cDr; i < n - 2; ++i)
		target[i + 2] = i;
	for (int i = cSt + 1; i < cDr; ++i) {
		target[i + 1] = i;
		L[i].inverse ^= 1;
	}


	target[cSt + 1] = n - 1;
	target[cDr + 1] = n - 2;
	L[n - 1].inverse ^= 1;
	L[n - 2].inverse ^= 1;

//	DEBUG();
//	for (int i = 0; i < n; ++i)
//		cerr << target[i] << ' ';
//	cerr << '\n';

	int emp = 0;
	for (int i = 0; i + emp < n; ++i) {
		if (L[target[i + emp]].el.size() == 0) {
			++emp;
			--i;
		} else {
			target[i] = target[i + emp];
		}
	}

 	for (int i = 0; i + emp < n; ++i) {
		if (target[i] == here[i]) 
			continue;
 		int a = i;
		int b = where[target[i]];
		swap(where[here[a]], where[here[b]]);
		swap(here[a], here[b]);
		swap(L[a], L[b]);
	}
	L.resize(L.size() - emp);
//	DEBUG();
//	cerr << "\n\n\n";
}

int get_rez (int ind) {
	int i = 0;
	while (ind > 0) {
		int n = L[i].el.size();
		if (ind <= n) {
			if (L[i].inverse == 0) {
				return L[i].el[ind - 1];
			} else {
				return L[i].el[L[i].el.size() - ind];
			}
		}
		ind -= n;
		++i;
	}
	return 0;
}


int main() {
	int n, m;
 	in >> n >> m;
	kMaxL = (sqrt(n) + 3) * 1.5;
	L.push_back(line(n));
	while (m--) {
		in >> st >> dr >> k;
		solve();
// 		cerr << "\n\n\n\n";
		out << get_rez(k) << '\n';
		if (L.size() >= kMaxL) {
			int N = L.size();
			for (int i = 0; i < N; ++i)
				L[i].Reverse();
			for (int i = 1; i < N; ++i) {
				if (L[i].inverse == 0)
					for (int j = 0; j < L[i].el.size(); ++j)
						L[0].el.push_back(L[i].el[j]);
				L[i].el.clear();
			}
			L.resize(1);
		}
	}
	return 0;
}
