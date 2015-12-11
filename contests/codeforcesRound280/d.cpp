//Problem D from Codeforces Round 280
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

int a[100005];

int main() {
	int n, A, B;
    cin >> n >> A >> B;
	swap(A, B);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
 		int64 L = 1LL << 50;
		int64 rez = 0;
		while (L) {
			int64 p = (rez + L) / A + (rez + L) / B;
			if (p < x)
				rez += L;
			L /= 2LL;
		}	
		rez++;
		if (rez % A == 0 and rez % B == 0)
			cout << "Both\n";
		else {
			if (rez % A == 0)
				cout << "Vanya\n";
			else
				cout << "Vova\n";
		}
	}
	return 0;
}
