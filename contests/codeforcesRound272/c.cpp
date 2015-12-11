//Problem C from Codeforces Round 272
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

const int inf = 0x3f3f3f3f, Mod = 1000000007;

int main() {
	int a, b;
    cin >> a >> b;
	
	int64 rez = 0;
	for (int i = 1; i < b; ++i) {
		rez += 1LL * i * a + (1LL * ((1LL * a * (a + 1) / 2) % Mod) * b) % Mod * i;
		rez %= Mod;
	}
	cout << rez;
	return 0;
}
