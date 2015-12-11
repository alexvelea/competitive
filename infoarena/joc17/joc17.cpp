#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("joc17.in");
ofstream out("joc17.out");

int main() {
	int T;
	in >> T;
	for (int t = 1; t <= T; ++t) {
		int n, m;
		in >> n >> m;
		n *= m;
		out << "Case " << t << ": ";
		if (n & 1)
			out << "First\n";
		else
			out << "Second\n";
	}
    return 0;
}
