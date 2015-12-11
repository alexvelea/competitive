//Problem B from Codeforces Round mindcodingRound2
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

map<string, bool> ap;

int main() {
	string txt;
	int rez = 0;
	cin >> txt; 
	for (int poz = 2; poz < 10; ++poz) {
		for (int i = 0; i < 10; ++i) {
			string r = "";
			for (int j = 0; j < poz; ++j) {
				r += txt[j];
			}
			r += '0' + i;
			for (int j = poz; j < 9; ++j) {
				r += txt[j];
			}
			if (ap[r] == false) {
				ap[r] = true;
				++rez;
			}
		}
	}
	cout << rez << '\n';
	return 0;
}
