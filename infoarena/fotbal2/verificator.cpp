#include <iostream>
#include <fstream>
using namespace std;

const int kMaxN = 50005;

int rez[kMaxN];

int main() {
    ifstream in("fotbal2.in");
	ifstream in2("fotbal2.out");

	int n, m, r;

	in >> n >> m;
	in2 >> r;

	for (int i = 1; i <= m; ++i) {
    	int a, b, w;
		in >> a >> b;
		in2 >> w;
		if (a != w and b != w)
			cerr << "Error! -> echipa invingatoare proasta\n";
		if (a == w) {
			rez[a]++;
			rez[b]--;
		} else {
			rez[b]++;
			rez[a]--;
		}
	}

	int mx = -100, mn = +100;
	bool ok = true;
	for (int i = 1; i <= n; ++i) {
		if (mx < rez[i])
			mx = rez[i];
		if (mn > rez[i])
			mn = rez[i];
		if ((rez[i] + 10000) % 2 == 1)
			ok = false;
	}

	if (ok and r != 0) {
		cerr << "Gresit -> ar trebui sa fie 0, dar nu e!\n";
	}
	if (mx - mn != r) {
		cerr << "Maximul - minimul nu da r .. gresit!\n";
	}
	
	return 0;
}
