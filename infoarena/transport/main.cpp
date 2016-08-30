#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream fin("transport.in");
ofstream fout("transport.out");


int main() {
	int n, k; fin >> n >> k;
	vector<int> el;
	for (int i = 1; i <= n; i += 1) {
		int x; fin >> x;
		el.push_back(x);
	}

	int rez = -1;
	for (int p = 30; p >= 0; p -= 1) {
		int mxSum = rez + (1 << p);
		int currentSum = 0, currentTrucks = 0;

		for (auto itr : el) {
			if (mxSum < itr) {
				currentTrucks = k + 1;
			}
		}

		for (auto itr : el) {
			if (currentSum + itr > mxSum) {
				currentSum = itr;
				currentTrucks += 1;
			} else {
				currentSum += itr;
			}
		}

		if (currentTrucks + 1 > k) {
			rez += (1 << p);
		}
	}

	rez += 1;
	fout << rez << '\n';
	return 0;
}