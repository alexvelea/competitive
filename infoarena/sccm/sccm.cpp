#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 80005;

ifstream in("sccm.in");
ofstream out("sccm.out");

vector<int> v1, v2;
vector<int> aib[max_n], el[max_n];
int poz[max_n];

int binary_search (vector<int> &el, int x) {
/*	int rez = 0;
    int p = 1;
	for (; p < int(el.size()); p <<= 1)
		;
	for (; p; p >>= 1)
		if (rez + p < int(el.size()))
			if (el[rez+p] <= x)
				rez += p;
	return rez;*/
	int y = lower_bound (el.begin(), el.end(), x+1) - el.begin() - 1;
	return y;
}

int aib_query (int ind, int x) {
	int rez = 0;
	for ( ; x; x -= (x) & (-x))
		rez = max(rez, aib[ind][x]);
	return rez;
}

int query (int ind, int nr) {
	int x = binary_search (el[ind], nr) + 1;
	return aib_query (ind, x);
}

void aib_update (int ind, int x, int val) {
   for ( ; x < int(aib[ind].size()); x += (x) & (-x))
		aib[ind][x] = max(aib[ind][x], val);
	return ;
}

void update (int ind, int nr, int val) {
	int x = binary_search (el[ind], nr) + 1;
	return aib_update (ind, x, val);
}   

int main() {
	int a, b, rez = 0;
	in >> a >> b;
	int n = min(a, b);
	v1.push_back(0);
	v2.push_back(0);
	for (int i = 1; i <= a; ++i) {
		int x;
		in >> x;
		if (x <= n) {
			v1.push_back (x);
			poz[x] = v1.size() - 1;
		}
	}
	for (int i = 1; i <= b; ++i) {
		int x;	
		in >> x;
		if (x <= n)
			v2.push_back (x);
	}
 	for (int i = 1; i <= n; ++i) {
		for (int j = i; j > i - ((i) & (-i)); --j) {
			el[i].push_back(v1[j]);
			aib[i].push_back(0);
		}
		aib[i].push_back(0);
		sort (el[i].begin(), el[i].end());
	}
 	for (int i = 1; i <= n; ++i) {
		int x = v2[i], nr = 0;
		for (int j = poz[x]; j; j -= (j) & (-j))
			nr = max(nr, query(j, x));
		nr++;
 		for (int j = poz[x]; j <= n; j += (j) & (-j))
 			update(j, x, nr);
		rez = max(rez, nr);
	}
	out << rez << "\n";
	return 0;
}
