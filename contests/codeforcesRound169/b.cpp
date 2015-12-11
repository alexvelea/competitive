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

const int INF=0x3f3f3f3f;

int main() {
	string S; cin >> S;
	vector<int> Cnt(26,0);
	FORIT (it, S) {
		Cnt[*it-'a']++;
	}
	int nr = 0;
 	for (int i=0; i<26; ++i) 
		if (Cnt[i]&1)
			++nr;
	if (nr < 2) {
		cout << "First\n";
	} else {
		if (nr&1) {
			cout << "First\n";
		} else {
			cout << "Second\n";
		}
	}
}
