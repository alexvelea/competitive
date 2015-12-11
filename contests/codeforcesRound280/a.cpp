//Problem A from Codeforces Round 280
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
	int n;
	cin >> n;
	for (int i = 1, rez = 0; ; ++i) {
		rez += i * (i + 1) / 2;
		if (rez > n) {
			cout << i - 1;
			return 0;
		}
	}
	return 0;
}
