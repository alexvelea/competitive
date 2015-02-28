#include <iostream>
#include <fstream>
using namespace std;

ifstream in("zlego.in");
ofstream out("zlego2.out");

int el[100000], val[100000], n;
long long rez;

void solve(int l) {
	for (int st = 0; st + l <= n; ++st) {
		bool ok = true;
		for (int i = 1; i <= l; ++i) {
			if (el[i] != el[st + i])
				ok = false;
		}
		if (ok)
			rez += val[st + l];
	}
}

int main() {
	int t;
	in >> t;
	while (t--) {
    	in >> n;
		for (int i = 1; i <= n; ++i)
			in >> el[i];
		for (int i = 1; i <= n; ++i)
 			in >> val[i];

		for (int i = 1; i <= n; ++i) {
        	rez = 0;
			solve(i);
			out << rez << '\n';
		}
	}
	out.close();
 	in.close();
}
