#include <fstream>
#include <iostream>
using namespace std;

ifstream in("kmax.in");
ofstream out("kmax.out");

const int kMaxN = 305;

int n, k, Mod;

void mod(int &a) {
	if (a >= Mod)
		a -= Mod;
}

int dp_old[kMaxN][kMaxN], dp_new[kMaxN][kMaxN];

int main() {
	in >> n >> k >> Mod;
	dp_old[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
//		for (int K = 1; K <= i; ++K, cerr << '\n')
//			for (int el = 1; el <= i; ++el)
//				cerr << dp_old[K][el] << ' ';
//		cerr << "\n\n";
		for (int K = 2; K <= min(k, i); ++K) {
			int sum = 0;
			for (int el = 2; el <= i; ++el) {
				sum += dp_old[K - 1][el - 1];
				mod(sum);
				dp_new[K][el] = sum;
			}
		}
		int sum = 0;
		for (int el = i; el >= 1; --el) {
			for (int K = 1; K <= min(k, i); ++K) {
				sum += dp_old[K][el];
				mod(sum);
			}
			dp_new[1][el] = sum;
		}
		for (int K = 1; K <= min(k, i); ++K)
			for (int el = 1; el <= i; ++el) {
				dp_old[K][el] = dp_new[K][el];
				dp_new[K][el] = 0;
			}
	}
	int sum = 0;
 	for (int K = 1; K <= k; ++K)
		for (int el = 1; el <= n; ++el) {
			sum += dp_old[K][el];
			mod(sum);
		}
	out << sum << '\n';
	return 0;
}
