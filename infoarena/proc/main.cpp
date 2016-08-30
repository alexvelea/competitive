#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream fin("proc.in");
ofstream fout("proc.out");


int main() {
	int n, k, nrProc; fin >> n >> k >> nrProc;
	int rez = -1;
	for (int p = 30; p >= 0; p -= 1) {
		int current = rez + (1 << p);
		int64 total = 0, one = 0;
		for (int i = 1; i <= nrProc; i += 1) {
			int now = int(current / i);
			one += now & 1;
			total += now - (now & 1);
		}

		if (total < (n - k) * 2 or (one + total < 2 * n - k)) {
			rez += (1 << p);
		}
	}
	rez += 1;
	fout << rez << '\n';
	return 0;
}