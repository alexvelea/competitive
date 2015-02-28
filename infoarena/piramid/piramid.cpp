//Problem piramid from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 1005;

ifstream in("piramid.in");
ofstream out("piramid.out");

int n;
int aib[2][kMaxN];

void aib_update(int a, int ind, int val) {
	++ind;
//	cerr << "Update -> " << a << '\t' << ind << '\t' << val << '\n';
	if (ind >= n + 1)
		ind = n;
	while (ind <= n) {
		aib[a][ind] += val;
		ind += ind & (-ind);
	}
}

int aib_query(int a, int ind) {
	++ind;
//	cerr << a << '\t' << ind << '\n';
	if (ind < 0)
		return 0;
	if (ind >= n + 1)
		ind = n;
	int rez = 0;
	while (ind) {
		rez += aib[a][ind];
		ind -= ind & (-ind);
	}
	return rez;
}

int up_st[kMaxN], st[kMaxN], up_dr[kMaxN], dr[kMaxN], here[kMaxN];
char el[kMaxN][kMaxN];

int rez = 0;

void solve() {
	for (int i = 0; i < n; ++i)
		up_st[i] = st[i] = dr[i] = up_dr[i] = aib[0][i] = aib[1][i] = 0;
	for (int l = 0; l < n; ++l) {
		st[0] = el[l][0] - '0';
		up_st[0] = el[l][0] - '0';
		for (int c = n - 1; c; --c)
			if (el[l][c] == '1')
				up_st[c] = up_st[c - 1] + 1;
			else
				up_st[c] = 0;

		for (int c = n - 1; c >= 0; --c)
			if (el[l][c] == '1')
				dr[c] = dr[c + 1] + 1;
			else
				dr[c] = 0;
		
		for (int c = 1; c < n; ++c)
			if (el[l][c] == '1')
				st[c] = st[c - 1] + 1;
			else
				st[c] = 0;

		for (int c = 0; c + 1 < n; ++c)
			if (el[l][c] == '1')
				up_dr[c] = up_dr[c + 1] + 1;
			else
				up_dr[c] = 0;

		vector<pair<int, int> > event;

        for (int i = 0; i < n; ++i) {
			int p = min((up_dr[i] - 1) * 2, dr[i] - 1);
//			cerr << p << '\t';
			if (p > 1) {
				event.push_back(make_pair(i + p, i));
//				cerr << "!!!!!\n" << i + p << '\t' << i << "\n";
			}
		}
//		cerr << '\n';
		sort(event.begin(), event.end());
		reverse(event.begin(), event.end());
		int itr = 0, total = 0;
		for (int i = n - 1; i >= 0; --i) {
			while (itr < int(event.size()) and event[itr].first >= i) {
				aib_update(event[itr].second % 2, event[itr].second, 1);
				total++;
				here[event[itr].second]++;
				++itr;
			}
			total -= here[i];
			here[i] = 0;
			int p = min(2 * (up_st[i] - 1), st[i] - 1);
// 			int _rez = rez;
			if (p > 1) 
				rez += total - aib_query(i % 2, p - i - 1);
// 			cerr << i << '|' << p << '|';   			
//			cerr << rez - _rez << '\n';
		}
//		cerr << "\n\n";
//		cerr << "~~~~ " << rez << '\n';
/* 		while (itr < int(event.size())) {
			aib_update(abs(event[itr].second) % 2, abs(event[itr].second), (event[itr].second > 0) ? (1) : (-1));
			++itr;
		}   	*/
		for (int i = 0; i <= n; ++i)
			aib[0][i] = aib[1][i] = 0;
	}
}

void rotate() {
	char _el[kMaxN][kMaxN];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			_el[j][n - i - 1] = el[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			el[i][j] = _el[i][j];
}

int main() {
	in >> n;
	for (int i = 0; i < n; ++i)
		in >> el[i];
	for (int i = 0; i < 4; ++i) {
		solve();
		rotate();
	}
	out << rez << '\n';
	return 0;
}
