//Problem c from mindcodingFinalRound2
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

char buffer[256];

char hexa(int x) {
	if (x < 10) {
		return '0' + x;
	}
	return 'A' + x - 10;
}

int main() {

    for (int i = 0; i < 256; ++i) {
		buffer[i] = '0';
	}

	ios::sync_with_stdio(false);
    string a, b;
	getline(cin, a);
	getline(cin, b);
	int A = 0, B = 0;
	int i = 0;
	while (i < int(a.size()) and a[i] != ',') {
		++i;
	}
	while (i < int(a.size())) {
		int x = 0;
		while (i < int(a.size()) and a[i] != ',') {
			x *= 10;
			x += a[i] - '0';
		}
		++i;
		where[++where[0]] = x;
	}

	int ind = 1;

	while (A < int(a.size()) and a[A] != ',') {
		if (a[A] == ' ') {
			while (A < int(a.size()) and a[A] == ' ') {
				++A;
			}
			while (B < int(b.size()) and b[B] == ' ') {
				++B;
			}
			continue;
		} else if (a[A] == '%') {
	   		++A;
 			if (a[A] == 'u') {
				//cifre
 				int x = 0;
				while (b[B] >= '0' and b[B] <= '9') {
					x *= 10;
					x += b[B] - '0';
					++A;
				}
 				while (x) {
					buffer[where[ind] + 1] = hexa(x % 16);
					x /= 16;
					buffer[where[ind]] = hexa(x % 16);
					x = 16;
					where[ind] += 2;
				}
			}
			if (a[A] == 'x') {
				string rez;
				while ((b[B] >= '0' and b[B] <= '9') or (b[B] >= 'A' and b[B] <= 'F')) {
					rez += b[B];
				}
				if (rez
			}

			++ind, ++A;
		} else {
			++A, ++B;
		}
	}
	return 0;
}
