//Problem A from Codeforces Round good.bye.2014
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

int n, t, el[300005];

int main() {
    cin >> n >> t;
	for (int i = 1; i < n; ++i) {
		cin >> el[i];
	}

	int nod = 1;
	while (nod != n and nod != t) {
   		nod += el[nod];
	} 

	if (nod == t)
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}
