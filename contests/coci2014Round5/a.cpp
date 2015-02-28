//Problem A from Codeforces Round coci.2014.round5
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

int main() {

	int el[20];

	for (int i = 1; i <= 8; ++i) {
		cin >> el[i];
	}
	for (int i = 1; i <+ 8; ++i) {
		el[i + 8] = el[i];
	}

    int mx = 0;

	for (int i = 1; i <= 8; ++i) {
		int rez = 0;
		for (int j = 0; j < 4; ++j) {
			rez += el[i + j];
		}
		if (rez > mx) {
			mx = rez;
		}
	}
	cout << mx;
	return 0;
}
