//Problem #C from Codeforces 235
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

int a, b;
void show(int x) {
	while (x and b) {
		cout << "1";
		x--;
		b--;
	}
}

int main() {
	cin >> a >> b;
	if (b + 1 < a) {
		cout << "-1\n";
		return 0;
	}
 	if (2 * (a + 1) < b) {
		cout << "-1\n";
		return 0;
	}
	b -= a - 1;
   	show(2);
	for (int i = 1; i < a; ++i) {
		cout << "01";
		show(1);
	}
	cout << "0";
	show(2);
	return 0;
}

