//Problem #A from Codeforces MindcodingFinal1
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

vector<string> rez;

string txt, init;
int viz[26], ap[26];

int main() {
	cin >> init;
	for (int i = 0; i < int(init.size()); ++i) {
		viz[init[i] - 'a']++;
	}
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
    	cin >> txt;
		for (int j = 0; j < 26; ++j)
			ap[j] = 0;
		for (int j = 0; j < int(txt.size()); ++j)
			ap[txt[j] - 'a']++;
		bool ok = true;
		for (int j = 0; j < 26; ++j)
			if (ap[j] > viz[j])
				ok = false;
		if (ok)
			rez.push_back(txt);
	}
	sort(rez.begin(), rez.end());
	for (int i = 0; i < int(rez.size()); ++i)
		cout << rez[i] << '\n';
    return 0;
}

