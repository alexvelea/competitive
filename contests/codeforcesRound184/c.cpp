#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT(it, v) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it)
#define mp make_pair
#define fi first
#define se second
#define th third
#define INF 0x3f3f3f3f

const int max_n = 100005;

int n, i, el[max_n];
deque< pair<int,int> > deq;

int main() {
	cin >> n;
	for (i=1; i<=n; ++i) {
		cin >> el[i];
	}
	for (i=1; i<=n; ) {
		int st = el[i], poz=i;
		while (i <= n && el[i] == st) {
			++i;
		}
		deq.push_back (mp(st,i-poz)); 
	}
	int mx = 0, good = 0;
 	while (deq.size()) {
 		pair<int,int> f = deq.front();
		deq.pop_front();
		good += ((f.se)&1);
		f.se >>= 1;
		mx = f.fi;
		if (deq.size()) {
	 		pair<int,int> s = deq.front();
			if (s.fi == 1+f.fi) {
				f.se += s.se;
				deq.pop_front();
			}
		}
		f.fi ++;
		if (f.se) {
			deq.push_front(f);
		}
	}
	printf("%d\n", mx - good + 1);
	return 0;
}
