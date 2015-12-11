#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}
void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

int nr = 0;

int main() {
	while(1) {
	system("./adriatic_generator");
	int x, y;
    ifstream ba("adriatic.in");
	int r[1005], c[1005];
    int mx_c = 0, mx_r = 0, mn_c = 2555, mn_r = 2555;

	int n;
	ba >> n;
	for (int i = 1; i <= n; ++i) {
		ba >> r[i] >> c[i];
		get_min(mn_c, c[i]);
		get_min(mn_r, r[i]);
		get_max(mx_c, c[i]);
		get_max(mx_r, r[i]);
	}
	bool ok = true;
	for (int i = 1; i <= n; ++i) {
   		if (r[i] == mx_r && c[i] == mx_c)
			ok = 0;
		if (r[i] == mn_r && c[i] == mn_c)
			ok = 0;
	} 
	if (ok == 0) {
		cerr << "Hello!";
		continue;
	}
	system("./adriatic");
	system("./adriatic_brut");

	ifstream in("adriatic.out");
	ifstream in2("adriatic2.out");
	int a = 0, b = 0;
	int sigma = 345;
	int mod = 666013;
	while (in >> x) {
		a *= sigma;
		a += x;
		a %= mod;
	}
	while (in2 >> y) {
		b *= sigma;
		b += y;
		b %= mod;
	}
	nr ++;
	if (a != b) { 
		cerr << "BAD!";
		assert(0);
	} else {
		cerr << nr << "\t";
		cerr << "OK!\n";
	}
	}
}
