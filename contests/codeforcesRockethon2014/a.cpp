//Problem #A from Codeforces rocket
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second

const int inf = 0x3f3f3f3f;

int main() {
	string txt;
	cin >> txt;
	int rez = 0;
	int nr = 1;
	for (int i = 1; i < txt.size(); ++i) {
		if (txt[i] != txt[i - 1]) {
			if (nr % 2 == 0)
				++rez;
			nr = 1;
		} else {
			++nr;
		}
	}
	if (nr % 2 == 0)
		++rez;
	cout << rez << '\n';
    return 0;
}

