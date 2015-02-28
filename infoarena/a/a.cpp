//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("a.in");
ofstream out("a.out");

const int inf = 0x3f3f3f3f;

int main() {
	int r, c, n;
	in >> r >> c;
	in >> n;
	while (n--) {
		int x;
		in >> x;
		int R, C;
		C = x % c;
		if (C == 0)
			C = c;
		R = (x - 1) / c;
		out << R + 1 << ' ' << C << ' ';
	}
    return 0;
}
