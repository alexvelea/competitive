#include <fstream>
#include <iostream>
using namespace std;

ifstream in("12perm.in");
ofstream out("12perm.out");

int rez = 0;

int perm[30], viz[30];

void bt(int poz, int n) {
	if (poz == n + 1) {
		int ok = true;
		for (int i = 1; i < n; ++i) {
			if (abs(perm[i] - perm[i + 1]) > 2) {
				ok = false;
			}
		}
		rez += ok;
		if (perm[1] != 1 and perm[n] != 1 and ok == true) {
			for (int i = 1; i <= n; ++i) {
		 		cerr << perm[i] << '\t';   
			}
			cerr << '\n';
		}
	} else {
		for (int i = 1; i <= n; ++i) {
			if (viz[i] == false) {
				perm[poz] = i;
            	viz[i] = true;
				bt(poz + 1, n);
				viz[i] = false;
			}

		}
	}

}

int main() {
	int n;
	in >> n;
	bt(1, n);
	out << rez;
}
