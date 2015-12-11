//Problem C from Codeforces Round 291
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;
const int kMod[2] = {1000000007, 1000000009};
int sigma = 7;

map<pair<int, int>, bool> M;

int main() {
	int n, m;
	ios::sync_with_stdio(false);
    cin >> n >> m;
	while (n--) {
		string txt;
		cin >> txt;
		int hsh[2] = {0, 0};
		for (int i = int(txt.size()) - 1; i; --i) {
			for (int d = 0; d < 2; ++d) {
				hsh[d] = (1LL * hsh[d] * sigma + (txt[i] - 'a' + 1)) % kMod[d];
			}
		}
		int s[2] = {1, 1};
		for (int i = 0; i < int(txt.size()); ++i) {
			M[make_pair(hsh[0], hsh[1])] = true;
			for (int d = 0; d < 2 and i + 1 < int(txt.size()); ++d) {
 				hsh[d] = (hsh[d] + 1LL * (txt[i] - 'a' + 1) * s[d] - 1LL * (txt[i + 1] - 'a' + 1) * s[d] + 4LL * kMod[d]) % kMod[d];   			
				s[d] = (1LL * s[d] * sigma) % kMod[d];
			}
		}
	}

 	while (m--) {
		string txt;
		cin >> txt;
		int hsh[2] = {0, 0};
		for (int i = int(txt.size()) - 1; i; --i) {
			for (int d = 0; d < 2; ++d) {
				hsh[d] = (1LL * hsh[d] * sigma + (txt[i] - 'a' + 1)) % kMod[d];
			}
		}
		int s[2] = {1, 1};
		bool ok = false;
		for (int i = 0; i < int(txt.size()); ++i) {
			if(M[make_pair(hsh[0], hsh[1])] == true)
				ok = true;
			for (int d = 0; d < 2 and i + 1 < int(txt.size()); ++d) {
				hsh[d] = (hsh[d] + 1LL * (txt[i] - 'a' + 1) * s[d] - 1LL * (txt[i + 1] - 'a' + 1) * s[d] + 4LL * kMod[d]) % kMod[d];
				s[d] = (1LL * s[d] * sigma) % kMod[d];
			}
		}
		if (ok) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
    
	return 0;
}
