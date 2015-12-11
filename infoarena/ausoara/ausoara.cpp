#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("ausoara.in");
ofstream out("ausoara.out");

const int inf = 0x3f3f3f3f;

vector<pair<int, int> > nr;
vector<int> rez;

int main() {
	int t;
	in >> t;
	for (int i = 1; i <= t; ++i) {
		int n;
		in >> n;
		for (int j = 1; j <= n; ++j) {
			int el;
			in >> el;
			nr.push_back(make_pair(el, i));
		}
	}
	sort(nr.begin(), nr.end());
	for (int st = 0; st < int(nr.size());) {
		int dr = st + 1;
		int mn = nr.size(), act = 1;

		if (nr[st].second != 1)
			mn = 0;
//		cerr << nr[st].first << '\t' << nr[st].second << '\t' << st << '\n';
		while (dr < int(nr.size()) and nr[dr].first == nr[st].first) {
			if (nr[dr].second == nr[dr - 1].second)
					++act;
			else {
				if (nr[dr].second != nr[dr - 1].second + 1)
					mn = 0;
				mn = min(mn, act);
				act = 1;
			}
			++dr;
		}
        mn = min(mn, act);

		if (nr[dr - 1].second != t)
			mn = 0;
		for (int i = 0; i < mn; ++i)
			rez.push_back(nr[st].first);
		st = dr;
	}
 	out << rez.size() << ' ';
	for (int i = 0; i < int(rez.size()); ++i)
		out << rez[i] << ' ';
    return 0;
}
