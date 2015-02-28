#include <fstream>
#include <iostream>
using namespace std;

int el[500005];

int main() {
	ifstream in("melodii.in");
	ofstream out("melodii.out");
	int t, r;
	in >> t >> r;
	el[0] = 1;
	el[1] = 1;
	el[2] = 2;
	int dr = 3;
	for (; not(el[dr - 1] == 1 and el[dr - 2] == 1); ++dr) {
		el[dr] = el[dr - 1] + el[dr - 2];
		if (el[dr] >= r)
			el[dr] -= r;
	}
 	r = dr - 2;
	
	for (; t; --t) {
		long long n;
		in >> n;
		out << el[n % r] << '\n';
	}
	return 0;
}
