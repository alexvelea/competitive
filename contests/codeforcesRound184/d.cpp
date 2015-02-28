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

const int MOD = 1000000007;

vector<int> beg;

int n, m, k;
int a, b;
int p2[1000005];
int i;

void get_min (int &a, int b) {
	if (a>b)
		a=b;
}
void get_max (int &a, int b) {
	if (a<b)
		a=b;
}

int max (long unsigned int a, int b) {
	if (a>b)
		return a;
	return b;
}

int main() {
	cin >> n >> m >> k;
	
	p2[0] = 1;
	for (i=1; i<=n; ++i) {
		p2[i] = p2[i-1] << 1;
		while (p2[i] >= MOD)
			p2[i] -= MOD;
	}

	for (;m;--m) {
		cin >> a >> b;
		if (((b-a) != 1) && ((b-a) != k+1)) {
			cout << "0\n";
			return 0;
		}
		if (b-a != 1) {
			beg.push_back(a);
		}
	}

	sort (beg.begin(), beg.end());
	beg.resize(unique(beg.begin(), beg.end()) - beg.begin());

	if (beg.size() && beg.front() + k < beg.back()) {
		cout << "0\n";
		return 0;
	}

	int rez;
	if (beg.size()) {  		
		rez = 0;
		int st = 1, dr = k+1;
		for (st=1; st<beg.front(); ++st, ++dr) {
			get_min (dr, n-k-1);
			if (beg.back() <= dr)
				rez += p2[max (dr-st-beg.size(), 0)];
			while (rez >= MOD)
				rez -= MOD;
        }
		get_min (dr, n-k-1);
		rez += p2[max (dr-st-beg.size()+1, 0)];
		while (rez >= MOD)
			rez -= MOD;
	} else {
		rez = 1;
		int st, dr = k+1;
		for (st=1; st+k+1<=n; ++st,++dr) {
			get_min (dr, n-k-1);
			rez += p2[dr-st];
			while (rez >= MOD)
				rez -= MOD;
		}
	}
	cout << rez << "\n";
	return 0;
}
