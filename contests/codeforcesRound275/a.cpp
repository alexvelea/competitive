//Problem A from Codeforces Round 2775
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 3005;

int el[kMaxN], target[kMaxN], who[kMaxN], where[kMaxN];
vector<pair<int, int> > rez;

bool srt(int a, int b) {
	return el[a] < el[b];
}

void sw(int a, int b) {
	swap(who[a], who[b]);
	swap(where[who[a]], where[who[b]]);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> el[i];
		target[i] = i;
 		who[i] = i;
		where[i] = i;
	}
	sort(target, target + n, srt);
	
    for (int i = 1; i <= n; ++i) {
		if (target[i] != who[i]) {
			int p = where[target[i]];
			rez.push_back(make_pair(i, p));
			sw(i, p);
		}
	}


	cout << rez.size() << '\n';
	for (auto it : rez)
		cout << it.first << ' ' << it.second << '\n';
	return 0;
}
