//Problem A from Codeforces Round 291
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
	string txt;
    cin >> txt;
	for (auto &itr : txt) {
		if (itr >= '5') {
			itr = '9' - itr + '0';
		}
	}
	int64 rez = 0;
	for (auto itr : txt) {
		rez *= 10LL;
		rez += itr - '0';
	}
	cout << rez;
	return 0;
}
