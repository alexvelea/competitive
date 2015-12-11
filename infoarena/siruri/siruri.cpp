#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("siruri.in");
ofstream out("siruri.out");

const int inf = 0x3f3f3f3f, kMaxN = 200005, kMaxLog = 18;

int order[kMaxLog][kMaxN];
int A[kMaxN], B[kMaxN];

int N, n, m, lg;

vector<pair<pair<int, int>, int> > query;
vector<pair<int, int> > ord;
vector<int> el;

int lcp(int a, int b) {
	int l = lg, rez = 0;
	if (a > b)
		swap(a, b);
	for (; l >= 0; --l)
		if (b + (1 << l) - 1 < N)
			if (order[l][a] == order[l][b]) {
				rez += 1 << l;
				a += 1 << l;
				b += 1 << l;
			}
	return rez;
}



int main() {
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> A[i];
	in >> m;
	for (int i = 1; i <= m; ++i)
		in >> B[i];
	for (int i = 1; i < n; ++i)
		el.push_back(A[i + 1] - A[i]);
	el.push_back(inf);

	int dr = el.size();

	for (int i = 1; i < m; ++i)
		el.push_back(B[i] - B[i + 1]);

	N = el.size();
	lg = 1;
	for (int i = 0; i < N; ++i)
		order[0][i] = el[i];
	for (; (1 << lg) < N; ++lg) {
		int LG = lg - 1;
		query.clear();
		for (int i = 0; i < N; ++i) {
			int x = -inf;
			if (i + (1 << LG) < N)
				x = order[LG][i + (1 << LG)];
			query.push_back(make_pair(make_pair(order[LG][i], x), i));
		}
		sort(query.begin(), query.end());
		int ind = 1;
		for (int st = 0; st < N; ++st) {
			if (st and query[st].first != query[st - 1].first)
				++ind;
			order[lg][query[st].second] = ind;
		}
	}
	--lg;

	for (int i = 0; i < N; ++i)
        ord.push_back(make_pair(order[lg][i], i));
	sort(ord.begin(), ord.end());

	int rez = 0, c1 = 0, c2 = 0;

	for (int i = 0; i + 1 < N; ++i) {
		int a = ord[i].second;
		int b = ord[i + 1].second;
		if (a > b)
			swap(a, b);
		if (a < dr and b >= dr) {
			int x = lcp(a, b);
			if (x > rez) {
				rez = x;
				c1 = a;
				c2 = b - dr;
			}
		}
	}
	out << rez + 1 << ' ' << c1 + 1 << ' ' << c2 + 1 << '\n';
    return 0;
}
