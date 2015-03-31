//Problem c from coci2014RoundFinal
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

priority_queue<pair<int64, int> > pq;

int main() {
	ios::sync_with_stdio(false);
	int64 m; cin >> m;
	int n, q; cin >> n >> q;

	vector<int> el, x;
	el.reserve(n + 5);
	x.reserve(n + 5);

	for (int i = 1; i <= n; ++i) {
		cin >> x[i]; el.push_back(x[i]);
	}
	el.push_back(m + 1);
	sort(el.begin(), el.end());

	int last = 0;
	for (auto itr : el) {
		if (last + 1 != itr) {
			pq.push(make_pair(itr - last - 1, -(last + 1)));
        }
		last = itr;
	}
	int qItr = 1;
	vector<int> query(q + 1);
	for (int i = 1; i <= q; ++i) {
		cin >> query[i];
		if (query[i] <= n) {
			cout << x[query[i]] << '\n';
			++qItr;
		} else {
			query[i] -= n;
		}
	}

	for (int act = 1; act <= 10; ++act) {
//		cerr << act << '\t' << qItr << '\n';
		int64 l = pq.top().first;
		int st = -pq.top().second;
		pq.pop();

		int m = (l - 1) / 2 + st;
//		cerr << "#\t" << l << '\t' << st << '\t' << m << '\n';
		if (m != st) {
			pq.push(make_pair(m - st, -st));
		}
		if (l - (m - st + 1) > 0) {
			pq.push(make_pair(l - (m - st + 1), -(m + 1)));
		}

		if (query[qItr] == act) {
			cout << m << '\n';
//			cerr << m << "!???\n";
			++qItr;
		}
		if (qItr == q + 1) {
			break;
		}
	}

	return 0;
}
