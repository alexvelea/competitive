#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("bancomat.in");
ofstream out("bancomat.out");

int ap[10];

bool solve(int x) {
	int v[] = {0, 1, 5, 10, 50, 100, 500};
	for (int i = 6; i; --i) {
		int d = x / v[i];
		d = min(d, ap[i]);
		x -= d * v[i];
		ap[i] -= d;
	}
	if (x == 0)
		return true;
	return false;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		for (int i = 1; i <= 6; ++i)
			in >> ap[i];
		int n;
		in >> n;
		bool ok = true;
		for (int i = 1; i <= n; ++i) {
			int val;
			in >> val;
			bool x = solve(val);
			if (x == false)
				ok = false;
		}
 		if (ok)
			out << "YES\n";
		else
			out << "NO\n";   	
	}
    return 0;
}
