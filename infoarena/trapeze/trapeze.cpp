#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

const int sigma = 100000000;

int primes[] = {0, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int ap[10], mx_ap[10];
int mx_ind, k;
double mx = 10000.0;

struct nr_mare {
	int cif[30];
	int nrcif;
 	nr_mare() {
		nrcif = 20;
 		for (int i = 0; i < nrcif; ++i)
			cif[i] = 0;
		cif[0] = 1;
	}
	void prod(int x) {
		for (int i = 0; i < nrcif; ++i)
			cif[i] *= x;
		for (int i = 0; i < nrcif; ++i) {
			while (cif[i] >= sigma) {
				cif[i] -= sigma;
				cif[i + 1] ++;
			}
		}
	}
	void show() {
		bool ok = false;
		for (int i = nrcif - 1; i >= 0; --i) { 
			int j = 0, el[8];
			for (j = 0; j < 8; ++j)
				el[j] = 0;
			j = 7;
			int x = cif[i];
			while (x) {
				el[j] = x % 10;
				x /= 10;
				j--;
			}
            for (int j = 0; j < 8; ++j)
				if (ok)
					cout << el[j];
				else 
					if (el[j]) {
						cout << el[j];
						ok = true;
					}
		}
	}
} rez;

void bt(int ind, int act) {
	if (act == k) {
		ind --;
		double rez = 0.0;
		for (int i = 1; i <= ind; ++i)
			rez += log(primes[i]) * ap[ind - i + 1];
		if (rez < mx) {
			mx = rez;
			mx_ind = ind;
			for (int i = 1; i <= ind; ++i)
				mx_ap[i] = ap[i];
		}
		return ;
	}
	for (int x = ap[ind - 1]; x; --x)
		if (act * (x + 1) <= k) {
			ap[ind] = x;
			bt(ind + 1, act * (x + 1));
		}
	return ;
}

int main() {
	freopen("trapeze.in","r",stdin);
	freopen("trapeze.out","w",stdout);
	ap[0] = 100;
	cin >> k;
	bt(1, 1);
	for (int i = 1; i <= mx_ind; ++i)
	a	for (int j = 1; j <= mx_ap[i]; ++j)
			rez.prod(primes[mx_ind - i + 1]);
	rez.show();
	return 0;
}

