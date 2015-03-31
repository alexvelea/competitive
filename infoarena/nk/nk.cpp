//Problem nk from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxVal = 32000;

ifstream in("nk.in");
ofstream out("nk.out");

bool viz[kMaxVal];
vector<int> primes;

int main() {
    for (int i = 2; i * i <= kMaxVal; ++i) {
		if (not viz[i]) {
			for (int j = i * i; j <= kMaxVal; j += i) {
				viz[j] = true;
			}
		}
	}
	for (int i = 2; i <= kMaxVal; ++i) {
		if (not viz[i]) {
			primes.push_back(i);
		}
	}

	int t; in >> t;
	return 0;
}
