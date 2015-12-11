#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("football.in");
ofstream out("football.out");

int64 s[50];
#define s (s + 10)

int main() {
	int t;
	in >> t;
	s[0] = 1;
	for (int i = 1; i <= 25; ++i) {
		if (i >= 3)
			s[i] += s[i - 3];
		if (i >= 6)
			s[i] += s[i - 6];
		if (i >= 2)
			s[i] += s[i - 2];
		s[i] += s[i - 1];
	}
	for (int i = 1; i <= t; ++i) {
		int x;
		in >> x;
		out << "Case " << i << ": " << s[x] << '\n';
	}
    return 0;
}
