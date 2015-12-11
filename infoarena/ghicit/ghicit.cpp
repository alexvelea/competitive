#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("ghicit.in");
ofstream out("ghicit.out");

const int kMaxN = 50500;

int lg = 0, n;
int order[16][kMaxN];

int lcp(int a, int b) {
	int l = lg, rez = 0;
	if (a > b)
		swap(a, b);
	for (; l >= 0; --l)
		if (b + (1 << l) - 1 < n)
			if (order[l][a] == order[l][b]) {
				rez += 1 << l;
				a += 1 << l;
				b += 1 << l;
			}
	return rez;
}

char txt[kMaxN];
vector<pair<pair<int, int>, int> > query;
vector<pair<int, int> > el;

int main() {
//	in.read(txt, kMaxN);
	in.getline(txt, kMaxN);
	n = strlen(txt);
	assert(n > 1);
	for (int i = 0; i < n; ++i)
		order[0][i] = int(txt[i]);

	lg = 1;
	for (; (1 << lg) < n; ++lg) {
		int LG = lg - 1;

		query.clear();
		for (int i = 0; i < n; ++i) {
			int x = -1;
			if (i + (1 << LG) < n)
				x = order[LG][i + (1 << LG)];
			query.push_back(make_pair(make_pair(order[LG][i], x), i));
		}
		sort(query.begin(), query.end());
		int ind = 1;
		for (int st = 0; st < n; ++st) {
			if (st and query[st].first != query[st - 1].first)
				++ind;
			order[lg][query[st].second] = ind;
		}
	}
	--lg;
	for (int i = 0; i < n; ++i)
		el.push_back(make_pair(order[lg][i], i));
	sort(el.begin(), el.end());
	
	int64 rez = el[0].second;
	for (int i = 0; i + 1 < n; ++i) {
		rez += el[i + 1].second;
		rez -= lcp(el[i].second, el[i + 1].second);
	}

	out << rez + n << '\n';
    return 0;
}
