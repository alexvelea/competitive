#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("substr.in");
ofstream out("substr.out");

const int kMaxN = 17000, kMaxLog = 15;

int order[kMaxLog][kMaxN];
vector<pair<pair<int, int>, int> > q;

string txt;
int n, k;

int LCP(int a, int b) {
	int l = 0, rez = 0;
	if (a > b)
		swap(a, b);
	while ((1 << l) < n)
		++l;
	for (; l >= 0; --l)
		if (b + (1 << l) - 1 < n) {
//			cerr << a << '\t' << b << '\t' << l << '\t' << '\t' << order[l][a] << '\t' << order[l][b] << '\n';
			if (order[l][a] == order[l][b]) {
				rez += 1 << l;
				a += 1 << l;
				b += 1 << l;
			}
		}
//	cerr << rez << '\n';
//	cerr << "\n\n";
	return rez;
}

pair<int, int> ord[kMaxN];

int main() {
	in >> n >> k;
	in >> txt;
 	for (int i = 0; i < n; ++i)
		order[0][i] = txt[i] - 'a';
	int mxl = 0;
	for (int l = 1; (1 << l) < n; ++l) {
		q.clear();
		for (int i = 0; i < n; ++i)
			if (i + (1 << (l - 1)) < n)
				q.push_back(make_pair(make_pair(order[l - 1][i], order[l - 1][i + (1 << (l - 1))]), i));
			else
				q.push_back(make_pair(make_pair(order[l - 1][i], -1), i));

		sort(q.begin(), q.end());
		int ind = 1;
		for (int st = 0; st < int(q.size()); ) {
			int dr = st;
			while (dr < int(q.size()) and q[st].first == q[dr].first)
				++dr;
			for (; st < dr; ++st)
				order[l][q[st].second] = ind;
   		 	++ind;
		}
		mxl = l;
	}
	for (int i = 0; i < n; ++i)
		ord[i] = make_pair(order[mxl][i], i);
	sort(ord, ord + n);
//	for (int i = 0; i < n; ++i)
//		cerr << ord[i].second << ' ';
//	cerr << "\n\n";
//	for (int i = 0; i <= mxl; ++i) {
//		cerr << ' ';
// 		for (int j = 0; j < n; ++j)
//			cerr << order[i][ord[j].second] << ' ';
//		cerr << '\n';
//	}
	if (k == 1) {
		out << n << '\n';
		return 0;
	}
	int rez = 0;
	for (int i = 0; i + k - 1 < n; ++i)
		rez = max(rez, LCP(ord[i].second, ord[i + k - 1].second));
	out << rez << '\n';
    return 0;
}
