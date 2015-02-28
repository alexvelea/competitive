//Problem cabine from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("cabine.in");
ofstream out("cabine.out");

int el[kMaxN];
int rez[kMaxN];

void ins(int x) {
	el[x] = 1;
	rez[++rez[0]] = x;
}

int main() {
	int n, k;
	in >> n >> k;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	if (el[1] == 0)
		ins(1);
	if (el[n] == 0)
		ins(n);
	for (int i = n - 1; i; --i) {
		if (el[i] == 0 and el[i + 1] == 0)
			ins(i);
	}

	for (int i = 1; i <= n; ++i)
		if (el[i] == 0)
 	   		ins(i);

	out << rez[k];
	return 0;
}
