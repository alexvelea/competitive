//Problem B from Codeforces Round rockethon2015
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
  	int64 m;
	int n;
	cin >> n >> m;
	int st = 1, dr = n;
	vector<int> rez(n + 1);
	for (int el = 1; el <= n; ++el) {
		int64 l = 0;
		if (n - el - 1 >= 0)
			l = (1LL << (n - el - 1));
		else 
			l = 0;

		if (l >= m) {
			rez[st] = el;
			++st;

		} else {
			rez[dr] = el;
			--dr;
			m -= l;
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << rez[i] << ' ';
	}                                  
	return 0;
}
