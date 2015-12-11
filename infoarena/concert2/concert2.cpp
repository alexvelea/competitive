#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("concert2.in");
ofstream out("concert2.out");

int el[2505];

int main() {
	int n, a, b;
	a--;
	b--;
	in >> n >> a >> b;	
 	int s = 1, act = 0, rez = 0;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	int last = el[1];
	for (int i = 2; i < n; ++i) {
		if (el[i] == last)
			continue;
		if (last < el[i]) {
//			cerr << "<\t";
			if (s == -1) {
				rez += act;
				act = 0;
			}
			act++;
			s = +1;
			if (act > a)
				act = a;
		} else {
//			cerr << ">\t";
			if (s == +1) {
				rez += act;
				act = 0;
			}
			act++;
			s = -1;
			if (act > b)
				act = b;
		}
		last = el[i];
	}
	rez += act;
	out << rez + 1 << '\n';
    return 0;
}
