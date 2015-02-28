#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int max_n = 3 * 100005;

int beat[max_n];
set<int> s;

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		s.insert(i);
	for (int i = 1; i <= m; ++i) {
		int l, r, x;
		cin >> l >> r >> x;
		set<int> :: iterator lit, rit;
		lit = s.lower_bound(l);
		if (*lit < l)
			++lit;
		rit = s.lower_bound(r);
		if (*rit == r)
			++rit;
		if (rit == s.begin())
			rit = s.end();
		for (; lit != rit; ) {
			lit = s.lower_bound(l);
			if (*lit < l)
				++lit;
			if (*lit == x)
				++lit;
			if (lit == rit)
				break;
            beat[*lit] = x;
			s.erase(lit);
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << beat[i] << ' ';
	return 0;
}
