//Problem D from Codeforces Round coci.2014.round5
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
	int n = txt.size();
    // n != 1
	int ok = 0;
	for (ok = 0; txt[ok] % 2 != txt[ok + 1] % 2; ++ok) {
		;
	}

	// min shit
	for (int i = 0; i <= ok; ++i)
		Mn[i] = txt[i] - '0';
	if (


	return 0;
}
