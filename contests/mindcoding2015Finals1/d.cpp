//Problem d from mindcoding2015Finals1
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int ord = 0;

int A[kMaxN], B[kMaxN];
int64 small[kMaxN], big[kMaxN], rez[kMaxN];

vector<int> vertex[kMaxN];

void df(int nod) {
	A[nod] = ++ord;
 	for (auto itr : vertex[nod]) {
		df(itr);	
	}
	B[nod] = ++ord;
}

int aib[2 * kMaxN];

int aibQuery(int where) {
	int rez = 0;
	while (where) {
		rez += aib[where];
		where -= where & (-where);
	}
	return rez;
}

void aibUpdate(int where, int val) {
	while (where < 2 * kMaxN) {
		aib[where] += val;
		where += where & (-where);
	}
	return ;
}

int main() {
	ios::sync_with_stdio(false);
 	int n; cin >> n;
	for (int i = 2; i <= n; ++i) {
		int f; cin >> f;
		vertex[f].push_back(i);
	}
	df(1);
	vector<pair<int64, int> > event;
	event.reserve(2 * n + 5);
	for (int i = 1; i <= n; ++i) {
		cin >> small[i];
		event.push_back(make_pair(small[i], -i));
	}

	for (int i = 1; i <= n; ++i) {
		cin >> big[i];
		event.push_back(make_pair(big[i], +i));
	}

	sort(event.begin(), event.end());
	for (auto itr : event) {
		int nod = abs(itr.second);
		if (itr.second > 0) {
			//query
			int64 total = aibQuery(B[nod]) - aibQuery(A[nod]);
			int64 r = 0;
			for (auto
				itr : vertex[nod]) {
				int64 now = aibQuery(B[itr]) - aibQuery(A[itr] - 1);
				r += 1LL * now * (total - now);
			}
			if (small[nod] <= big[nod]) {
				r += 2 * total + 1;
			}
			rez[nod] = r;
		} else {
			//insert
			aibUpdate(A[nod], +1);
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << rez[i] << '\n';
	}
	return 0;
}
