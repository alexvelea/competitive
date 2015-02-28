//Problem #A from Codeforces mindcode
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

string el, txt[10];
int x[10];

void bt(int ind) {
	if (ind == el.size()) {
		for (int i = 0; i < el.size(); ++i) {
			cout << txt[el[i] - '0'][x[i]];
		}
		cout << '\n';
		return ;
	}
	for (int i = 0; i < int(txt[el[ind] - '0'].size()); ++i) {
		x[ind] = i;
		bt(ind + 1);
	}
}

int main() {
	for (int i = 0; i < 10; ++i) {
		cin >> txt[i];
		sort(txt[i].begin(), txt[i].end());
	}
    cin >> el;
	bt(0);
	return 0;
}

