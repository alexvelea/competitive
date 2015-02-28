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

const int max_n = 5005;

int main() {
	string S; cin >> S;
	int n = S.size();
	int Grundy[max_n];
	Grundy[0] = 0;
	Grundy[1] = 1;
	for (int i = 2; i <= n; ++i) {
		vector <int> Found;
		Found.clear();
		for (int j = 1; j <= i; ++j) {
			Found.push_back (Grundy[max(0,j-2)] ^ Grundy[max(0, i-j-1)]);
		}
		sort (Found.begin(), Found.end());
		Found.resize (unique (Found.begin(), Found.end()) - Found.begin());
		int act = 0;
		FORIT (it, Found) {
			if (act != *it) {
				Grundy[i] = act;
				break;
			}
			act ++;
		}
		if (!Grundy[i])
			Grundy[i] = act;
	}
	bool Valid[max_n];
 	for (int i = 0; i < n; ++i) {
		if (i == 0 || i == n-1) 
			Valid[i] = false;
		else {
			if (S[i-1] == S[i+1])
				Valid[i] = true;
			else
				Valid[i] = false;
		}
	}
	int x = 0, act = 0;
	for (int i = 0; i < n; ++i) {
		if (Valid[i] == false) {
			x ^= Grundy[act];
			act  = 0;
		} else {
			++act;
		}
	}
	if (x == 0) {
		cout << "Second\n";
	} else {
		act = 0;
		for (int i = 0; i < n; ++i) {
			if (Valid[i] == false) {
				for (int j = i-act; j < i; ++j) {
					if ((x ^ Grundy[act] ^ Grundy[max(0, j-i+act-1)] ^ Grundy[max(0, i-j-2)]) == 0) {
						cout << "First\n" << j+1 << "\n";
						return 0;
					}
				}
				act = 0;
			} else {
				++act;
			}
	   	}
	}
	return 0;
}
