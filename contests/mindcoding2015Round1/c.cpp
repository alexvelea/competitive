//Problem C from Codeforces Round mindcodingRound1
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

string rez[10];

void expand(int k) {
	while (k--) 
	for (int i = 0; i < 10; ++i)
		if (i % 2 == 0)
			rez[i] += '-';
		else
			rez[i] += ' ';
}

int main() {
    rez[0] += "----|-\\----";
    rez[1] += "    |  }   ";
    rez[2] += "----|-/----";
    rez[3] += "    |/   4 ";
    rez[4] += "---/|------";
    rez[5] += "  / |    4 ";
    rez[6] += "-{--|-\\----";
    rez[7] += "  \\_|_/    ";
    rez[8] += "----|\\-----";
    rez[9] += "    |_}    ";
	cin >> n;
	while (n--) {
		int m = rez[0].size();
		expand(5);
		string txt;
		cin >> txt;
		txt += "    ";
	}
	expand(4);
}

