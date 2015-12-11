//Problem A from Codeforces Round coci.2014.round4
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

const int inf = 0x3f3f3f3f;

int z[4] = {1, 10, 100, 1000};

int rez = inf, sum = 0, n;

int ap[10];

void bt(int act, int inside, int nr) {
	if (inside == 4 or act == 10) {
		int s = sum, aux = nr;
		while (aux) {
			s -= aux % 10;
			aux /= 10;
		}

		if (s % 3 == 0 and rez > nr)
			rez = nr;

		return ;
	}
	for (int i = 0; inside <= 4 and i <= ap[act]; ++inside) {
		bt(act + 1, inside, nr);
		nr += z[inside] * act;
	}
}

string txt;

int main() {
	cin >> txt;
	n = txt.size();
	for (int i = 0; i < n; ++i) {
		ap[txt[i] - '0']++;
	}
	
	if (ap[0] == 0) {
		cout << "-1\n";
		return 0;
	}

	for (int i = 1; i <= 9; ++i)
		sum += i * ap[i];
	
	bt(1, 0, 0);
	
	while (rez) {
        ap[rez % 10]--;
		rez /= 10;
	}

	int ok = false;
	for (int i = 1; i <= 9; ++i)
		if (ap[i])
			ok = true;
	
	if (ok == false) {
		cout << "-1\n";
		return 0;
	}

	for (int i = 9; i >= 0; --i) {
		while (ap[i]) {
			ap[i]--;
			cout << i;
		}
	}
	return 0;
}
