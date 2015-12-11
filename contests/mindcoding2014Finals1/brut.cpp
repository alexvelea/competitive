#include <fstream>
#include <iostream>
using namespace std;
int val[100005];
int n, q;

ifstream in("date.in");
ofstream out("date.out");

int main() {
	in >> n >> q;
	while (q--) {
		int t;
		in >> t;
		if (t == 1) {
			int a, b;
			in >> a >> b;
			for (int i = a; i <= b; ++i)
				val[i] ^= 1;
		} else {
			int x;
			int st, dr;
			in >> x;
			for (st = x; val[x] == val[st] and st; --st)
				;
			for (dr = x; val[x] == val[dr] and dr <= n; ++dr)
				;
			st++;
			dr--;
			out << val[x] << ' ' << st << ' ' << dr << '\n';
		}
	}
	in.close();
	out.close();
	return 0;
}

