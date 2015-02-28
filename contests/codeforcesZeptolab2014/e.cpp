//Problem #E from Codeforces zepto
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 300005;

int64 a[kMaxN], b[kMaxN];
bool split[kMaxN];
vector<pair<int, int> > event;
int rez[kMaxN];

int main() {
	int n, w;
	cin >> n >> w;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
		a[i] *= 2;
		b[i] *= 2;
		if (b[i] >= 2 * a[i]) {
			event.push_back(make_pair(a[i], i));
			event.push_back(make_pair(b[i] - a[i], i));
		} else {
			split[i] = true;
			int64 s = b[i] 
			/ 2;
			event.push_back(make_pair(s, i));
			event.push_back(make_pair(s, i));
		}
	}

	sort(event.begin(), event.end());
	for (int i = 0; i < w; ++i) {
		rez[event[i].second]++;
	}
	
	bool bad = false;
	int nr_poz = 0, poz;
	for (int i = 1; i <= n; ++i)
		if (split[i] == true and rez[i] == 1) {
			bad = true;
			poz = i;
			nr_poz++;
		}

	if (bad == false) {
		int64 sum = 0;
		for (int i = 0; i < w; ++i)
			sum += event[i].first;
		
		cout << sum / 2<< '\n';
		for (int i = 1; i <= n; ++i)
			cout << rez[i];
		cout << '\n';
		return 0;
	}

	rez[event[w - 1].second]++;

	assert(nr_poz <= 1);
 	int mn = 2 * inf, mn_poz;
	for (int i = w; i < 2 * n; ++i) {
		if (split[event[i].second] != true) {
			if (mn > event[i].first) {
				mn = event[i].first;
				mn_poz = event[i].second;
			}
		}
		if (split[event[i].second] == true and rez[event[i].second] == 0) {
			if (mn > a[event[i].second]) {
				mn = a[event[i].second];
				mn_poz = event[i].second;
			}
		}
	}

    int mx2 = -2 * inf, mx2_poz  = 0;
 	for (int i = 1; i <= n; ++i) {
		if (split[i] == true and rez[i] != 0) {
			if (mx2 < b[i] - a[i]) {
            	mx2 = b[i] - a[i];
				mx2_poz = i;
			}
		}
		if (split[i] == false) {
        	if (rez[i] == 2) {
				if (mx2 < b[i] - a[i]) {
					mx2 = b[i] - a[i];
					mx2_poz = i;
				}
			}
			if (rez[i] == 1) {
				if (mx2 < a[i]) {
					mx2 = a[i];
					mx2_poz = i;
				}
			}
		}
	}

	mn = 2 * event[w - 1].first - mn;
	if (mn > mx2) {
		int poz = event[w - 1].second;
		rez[poz] = 0;
		rez[mn_poz]++;
	} else {
		rez[mx2_poz]--;
	}

	int64 sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (rez[i] >= 1)
			sum += a[i];
		if (rez[i] == 2)
			sum += b[i] - a[i];
	}
	cout << sum / 2 << '\n';
	for (int i = 1; i <= n; ++i)
		cout << rez[i];
	cout << '\n';
	return 0;
}

