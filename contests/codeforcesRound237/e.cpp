//Problem #E from Codeforces 237
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f;

string txt;

int main() {
	cin >> txt;
	int n = txt.size();
	char c = txt[n - 1];
	for (int i = 0; i < n; ++i) {
    	if (txt[i] == c)
			el[i] = -1;
		else
			el[i] = 1;
	}
	mn[0] = el[0];
	int mx = 0, sum = el[0];
    for (int i = 1; i < n; ++i) {
		sum += el[i];
		if (mx < sum)
			mx = sum;
	}
	return 0;
}

