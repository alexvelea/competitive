#include <fstream>
#include <iostream>
using namespace std;

ifstream in("turneu.in");
ofstream out("turneu.out");

const char answer[2][10] = {"NO\n", "YES\n"};
const int max_n = 100005;

long long sum[max_n];
int nr[max_n];

int main() {
	int T;
	in >> T;
	while (T--) {
		int n;
		bool ok = true;
		in >> n;
		for (int i = 1; i <= n; ++i) {
			double el;
			in >> el;
			el *= 2.0;
			if (el != int(el)) /* for points that do not end in .5 */
				ok = false;
			nr[i] = int(el);
		}
		sum[n + 1] = 0;
		for (int i = n; i; --i)
			sum[i] = 1LL * sum[i + 1] + nr[i];
 		for (int i = n; i; --i) 
			if (sum[i] > 1LL * (i + n - 2) * (n - i + 1)) {
				ok = false;
			}
		if (sum[1] != 1LL * n * (n - 1))
			ok = false;
		out << answer[ok];
	}
	return 0;
}
