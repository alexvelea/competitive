#include <fstream>
using namespace std;

const int kMaxN = 5e6 + 5;

#define int64 long long

int el[kMaxN], deq[kMaxN];

ifstream fin("deque.in");
ofstream fout("deque.out");

int main() {
	int n, k; fin >> n >> k;
	for (int i = 1; i <= n; i += 1) {
		fin >> el[i];
	}

	int dSt = 1, dDr = 0;
	int64 dSum = 0;
	for (int i = 1; i <= n; i += 1) {
		if (deq[dSt] <= i - k) {
			dSt += 1;
		}

		while (dDr >= dSt and el[i] <= el[deq[dDr]]) {
			dDr -= 1;
		}

		deq[++dDr] = i;
		if (i >= k) {
			dSum += el[deq[dSt]];
		}
	}

	fout << dSum << '\n';
	return 0;
}