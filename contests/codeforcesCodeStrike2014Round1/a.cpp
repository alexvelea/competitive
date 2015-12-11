//Problem #A from Codeforces code_strike_2014_round_1
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

int main() {
	int n, k;
	char txt[105];
	cin >> n >> k;
 	cin >> txt;
	int a = k - 1, b = n - k;
	k--;
	if (a <= b) {
		for (int i = k; i > 0; --i)
			printf("LEFT\n");
		printf("PRINT %c\n", txt[0]);
		for (int i = 1; i < n; ++i)
			printf("RIGHT\nPRINT %c\n", txt[i]);
	} else {
		for (int i = k; i < n - 1; ++i)
			printf("RIGHT\n");
		printf("PRINT %c\n", txt[n - 1]);
		for (int i = n - 2; i >= 0; --i)
			printf("LEFT\nPRINT %c\n", txt[i]);
	}
    return 0;
}

