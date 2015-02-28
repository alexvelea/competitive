#include <fstream>
#include <iostream>
using namespace std;

ifstream in("puncte.in");
ofstream out("date.out");

#define int64 long long

const int kMaxN = 100005, inf = 0x3f3f3f3f;

int n, m;
int x[kMaxN], y[kMaxN];

int main() {
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		in >> x[i] >> y[i];
	while (m--) {
		int X;
		in >> X;
		int64 mn = 1LL * inf * inf;

		for (int i = 1; i <= n; ++i)
			if (mn > 1LL * (X - x[i]) * (X - x[i]) + 1LL * y[i] * y[i])
				mn = 1LL * (X - x[i]) * (X - x[i]) + 1LL * y[i] * y[i]; 

		out << mn << '\n';
	}
	in.close();
	out.close();
	return 0;
}
