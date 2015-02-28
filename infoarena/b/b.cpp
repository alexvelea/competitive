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

ifstream in("b.in");
ofstream out("b.out");

const int kMaxP = 1005;

int rez[kMaxP];

pair<int, int> coord[kMaxP], null_pair;

int abs(int a) {
	if (a > 0)
		return a;
	return -a;
}

int distance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
	int r, c, n;
	in >> r >> c;
	in >> n;
	while (n--) {
		int x, color;
		in >> x >> color;
		
		int R, C;
		C = x % c;
		if (C == 0)
			C = c;
		R = (x - 1) / c;
		R++;
		if (coord[color] == null_pair)
			coord[color] = make_pair(R, C);
		else {
			rez[color] = distance(coord[color], make_pair(R, C));
		}
	}
	for (int i = 1; rez[i] != 0; ++i)
		out << rez[i] << ' ';
    return 0;
}
