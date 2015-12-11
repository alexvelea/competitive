//Problem A from Codeforces Round 292
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

char cif[20];
int ap[20];

void add(int j, int sign) {
	for (int i = 2; i <= j; ++i) {
		while (j % i == 0) {
			j /= i;
			ap[i] += sign;
		}
	}
	return ;
}

int main() {
	int n;
    cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> cif[i];
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 2; j <= cif[i] - '0'; ++j) {
			add(j, +1);
		}
	}

	vector<int> rez;

    for (int i = 7; i >= 2; --i) {
		while (ap[i] > 0) {
			rez.push_back(i);
			for (int p = 2; p <= i; ++p)
				add(p, -1);                	
		}
	}

	for (int i = 2; i <= 7; ++i) {
		if (ap[i] != 0)
			cerr << "!!!\n";
	}
	for (auto itr : rez)
		cout << itr;

	return 0;
}
