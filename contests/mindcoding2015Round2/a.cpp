//Problem A from Codeforces Round mindcodingRound2
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
	int c1, c2;
	while (cin >> txt) {
	cin >> c1 >> c2;
	if (c1 == 0 and c2 == 0 and txt == "0")
		return 0;
	for (auto &itr : txt) {
		if (itr - '0' == c1)
			itr = c2 + '0';
	}
	cout << atoi(txt.c_str()) << '\n';
	}
	return 0;
}
