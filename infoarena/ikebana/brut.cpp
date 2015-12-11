#include <iostream>
#include <fstream>
using namespace std;

ifstream in("ikebana.in");
ofstream out("ikebana.out");

long long rez = 0;
int n, p, t;

int el[100];

void bt(int ind) {
	if (ind == n + 1) {
    	rez++;
		return ;
	}
	if (ind + 1 <= n) {
 		if (el[ind - 1] == 2) {
			el[ind + 1] = 3;
			bt(ind + 2);
			el[ind + 1] = 0;
		}
		if (el[ind - 1] == 3) {
			el[ind + 1] = 3;
			bt(ind + 2);
			el[ind + 1] = 0;
		}
	}
	for (int i = 1; i <= t - 4; ++i)
		bt(ind + 1);
	el[ind] = 2;
	bt(ind + 1);
	el[ind] = 3;
	bt(ind + 1);
	el[ind] = 0;

	int poz = ind;
	while (poz > 0 and el[poz] != 1)
		--poz;
	if ((ind - poz - 1 >= p) or (poz == 0)) {
		el[ind] = 1;
		bt(ind + 1);
		el[ind] = 0;
	}
	return ;
}

int main() {
	in >> n >> p >> t;
	bt(1);
	cerr << rez << '\n';
	return 0;
}
