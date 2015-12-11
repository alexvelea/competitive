//Problem B from Codeforces Round memsql
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
	int a, b;
 	cin >> a >> b;
	if (a == 1) {
		cout << "1 0\n0 " << b << "\n0 0\n1 " << b;
		return 0;
	}
	if (b == 1) {
		cout << "0 0\n" << a << " 1\n0 1\n" << a << " 0\n";
		return 0;
	}

	if (a < b and a != 0) {
		cout << "1 0\n" << a << ' ' << b << '\n' << "0 0\n" << a - 1 << ' ' << b << '\n';
	} else {
		cout << "0 1\n" << a << ' ' << b << '\n' << "0 0\n" << a << ' ' << b - 1 << '\n';
	}
	return 0;
}
