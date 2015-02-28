#include <fstream>
using namespace std;

ifstream in("perm.in");
ofstream out("perm.out");

long long sol[205];

int main() {
	int n, k;
	in >> n >> k;
	sol[1] = 1;
	for (int i = 2; i <= n; ++i)
		for (int j = k; j; --j) {
			if (j != k)
				sol[j + 1] += sol[j];
			sol[j] = sol[j * 1LL] * (i- 1);
		}
	out << sol[k] << '\n';
	return 0;
}
