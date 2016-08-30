//Problem d @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 5005, kMod = 1e9 + 7;

#define int64 long long

bool isBigger[kMaxN][kMaxN];
int endHere[kMaxN][kMaxN];

string txt;

void MOD(int &a) {
	if (a >= kMod) {
		a -= kMod;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	cin >> txt;
	txt = "#" + txt;

	for (int l = 1; l <= n; l += 1) {
		int currentL = 0;
		for (int st = 1, dr = st + l; dr + l - 1 <= n; st += 1, dr += 1) {
			while (st + currentL + 1 < dr and txt[st + currentL] == txt[dr + currentL]) {
				currentL += 1;
			}

			if (txt[dr + currentL] > txt[st + currentL]) {
				isBigger[dr][l] = true;
			}

			// cerr << l << '\t' << st << '\t' << dr << '\t' << currentL << '\n';

			currentL -= 1;
			if (currentL < 0) {
				currentL = 0;
			}
		}
		// cerr << '\n';
	}

	// cerr << "!";

	endHere[0][0] = 1;
	
	for (int i = 1; i <= n; i += 1) {
		for (int itr = 1; itr < kMaxN; itr += 1) {
			endHere[i - 1][itr] += endHere[i - 1][itr - 1];
			MOD(endHere[i - 1][itr]);
		}

		if (txt[i] == '0') {
			continue;
		}

		for (int currentL = 1; i + currentL - 1 <= n; currentL += 1) {
			int exp = 0;
			if (isBigger[i][currentL]) {
				exp = endHere[i - 1][currentL];
			} else {
				exp = endHere[i - 1][currentL - 1];
			}
			endHere[i + currentL - 1][currentL] += exp;
			// cerr << i << '\t' << currentL << '\t' << exp << '\n';
			MOD(endHere[i + currentL - 1][currentL]);
		}
		// cerr << "\n\n";
	}

	int rez = 0;
	for (int i = 0; i < kMaxN; i += 1) {
		rez += endHere[n][i];
		MOD(rez);
	}
	cout << rez << '\n';
	return 0;
}
