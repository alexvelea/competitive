#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int st[30], dr[30], sum_st, sum_dr;
string txt;

int main() {
	cin >> txt;
	int n = txt.size();
	int i = 0;
	while (txt[i] != '|') {
		++sum_st;
		st[txt[i] - 'A'] = true;
		++i;
	}
	++i;
	while (i < n) {
		++sum_dr;
		dr[txt[i] - 'A'] = true;
		++i;
	}
   	cin >> txt;
	if ((sum_st + sum_dr + txt.size()) % 2 == 0) {
		if (min(sum_st, sum_dr) + txt.size() >= max(sum_st, sum_dr)) {
 			for (int i = 0; i < 26; ++i)
				if (st[i] == 1)
					cout << char('A' + i);
			int ind = 0;
 			for (int i = sum_st; i < (sum_st + sum_dr + txt.size()) / 2; ++i) {
				cout << txt[ind];
				++ind;
			}
			cout << '|';
			for (int i = 0; i < 26; ++i)
				if (dr[i] == 1)
					cout << char('A' + i);
			while (ind < txt.size()) {
				cout << txt[ind];
				++ind;
			}
		} else {
   		cout << "Impossible\n";
		}
	} else {
		cout << "Impossible\n";
	}
	return 0;
}
