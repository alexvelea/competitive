//Problem #B from Codeforces rocket
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

const int inf = 0x3f3f3f3f;

void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

string text;
int best[1005];

int main() {
	int rez = 1;
 	cin >> text;
	best[0] = 1;
	for (int i = 1; i < text.size(); ++i) {
		best[i] = 1;
    	for (int j = 0; j < i; ++j)
			if (text[i] == text[j] and (i - j) % 2 == 1) {
				get_max(best[i], best[j] + 1);
            }
		get_max(rez, best[i]);
	}
	cout << rez << '\n';
    return 0;
}

