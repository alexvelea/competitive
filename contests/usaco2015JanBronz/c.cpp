//Problem C from Codeforces Round usaco2015JanBronz
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long 	long

const int inf = 0x3f3f3f3f;

ifstream in("whatbase.in");
ofstream out("whatbase.out");

map<int, int> base;

int main() {
	int q;
	in >> q;
	while (q--) {
		char a[3], b[3];
		in >> a >> b;
		base.clear();
		for (int i = 0; i < 3; ++i) {
			a[i] -= '0';
			b[i] -= '0';
		}
		swap(a[0], a[2]);
		swap(b[0], b[2]);

		for (int i = 10; i <= 15000; ++i) {
			base[a[0] + i * a[1] + i * i * a[2]] = i;
		}

		for (int i = 10; i <= 15000; ++i) {
			int nr = b[0] + i * b[1] + i * i * b[2];
			if (base[nr] != 0) {
				out << base[nr] << ' ' << i << '\n';
				break;
			}
		}
	}
	return 0;
}
