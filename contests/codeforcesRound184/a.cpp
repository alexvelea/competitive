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

vector<int> rez[512];

int n, el[105];
int i, j, st;

int ok (int a, int b){
 	int rez = 0;
	for (int cif=0; cif<3; ++cif){
		if ((a&1) && ((b%10)!=0))
			return 0;
 
 		if ((a&1) || ((b%10)!=0))
			rez |= 1<<cif;
		a >>= 1;
		b /= 10;
	}
	return rez;
}

int main() {
	bool zero = 0;
	cin >> n;
	for (i=1; i<=n; ++i) {
		cin >> el[i];
 		if (el[i] == 0) {
		    i--;
			n--;
			zero = 1;
		}
	}
 	for (i=1; i<=n; ++i) {
		for (j=0; j<=16; ++j) {
			st = ok(j,el[i]);
			if (st) {
				if (rez[st].size() < rez[j].size()+1) {
					rez[st].clear();
					FORIT (it,rez[j])
						rez[st].push_back(*it);
					rez[st].push_back(el[i]);
				}
			}
		}
	}
	int mx = 0, poz=0;
	for (j=0; j<=16; ++j) {
		if (rez[j].size() > mx) {
			mx = rez[j].size();
			poz = j;
		}
	}
	cout << mx+zero << "\n";
	FORIT(it,rez[poz])
		cout << *it << " ";
	if(zero)
		cout <<"0 ";
	return 0;
}
