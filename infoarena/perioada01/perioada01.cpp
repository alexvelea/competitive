//Problem perioada01 from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxP = 1000005;

ifstream in("perioada01.in");
ofstream out("perioada01.out");

int pi[kMaxP], a[kMaxP];
int n, p;

void make_prefix() {
	int q = 0;
	for (int i = 2; i <= p; ++i) {
		while (q && a[q + 1] != a[i])
			q = pi[q];
		if (a[q + 1] == a[i])
			++q;
		pi[i] = q;
	}
	return ;
}

int main() {
	in >> n >> p;
	for (int i = 1; i <= p; ++i)
		in >> a[i];
	for (int i = p; i; --i)
		a[i] -= a[1];
	a[p + 1] = n;
	for (int i = 1; i <= p; ++i)
		a[i] = a[i + 1] - a[i];
 	make_prefix();
	int r = pi[p];
 	while (r) {
		if (r % (p - r) == 0)
			break;
		r = pi[r];
	}   
	
	if (r == 0) {
		out << "-1\n";
	} else {
		r = p - r;
		int R = 0;
		for (int i = 1; i <= r; ++i)
			R += a[i];
		out << R << '\n';
	}
	return 0;
}
