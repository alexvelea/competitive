#include <fstream>
#include <iostream>
using namespace std;

const int max_k = 30005;
ifstream in("camion.in");
ofstream out("camion.out");

int l_up[max_k], l_down[max_k], c_st[max_k], c_dr[max_k];

int main() {
	int n, m, k, c;
 	in >> n >> m >> k >> c;
	for (int i = 1; i <= k; ++i)
		in >> l_up[i] >> c_st[i] >> l_down[i] >> c_dr[i];
	for (int i = 1; i <= n; ++i) {
		int x = c;
		for (int j = k; j; --j)
			if (l_up[j] <= i && i <= l_down[j] && c_st[j] <= x)
				x += c_dr[j] - c_st[j] + 1;
		if (x > m)
			out << "0\n";
		else
			out << x << '\n';
	}
	return 0;
}
