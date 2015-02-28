#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int max_n = 30005;
const int INF = 0x3f3f3f3f;

int n, el[max_n];

int second_sol (bool afisare) {
	int st, dr;
	int rez = INF;
	for (int i = 1; i<n; ++i) 
		for (int j = i+1; j < n; ++j) {
			int s = 0;
			int mx = -INF;
			for (int l = 1; l <= i; ++l)
				if (el[l] > mx)
					mx = el[l];
			s += mx;
			mx = -INF;
 			for (int l = i+1; l <=j; ++l)
				if (el[l] > mx )
					mx = el[l];
			s += mx;
			mx = -INF;
 			for (int l = j+1; l <= n; ++l) 
				if (el[l] > mx)
					mx = el[l];
			s += mx;
			if (rez > s) {
				rez = s;
 				st = i;
				dr = j;
			}
		}
	if (afisare)
		cerr << rez << "\n" << st << " " << dr;
	return rez;
}

int rez, first, second;

void solve() {
	int mx = -INF, poz = 0;
	for (int i = 1; i <=n; ++i) 
		if (mx <= el[i]) {
			mx = el[i];
			poz = i;
		}
	int mx2 = -INF;
	for (int i = 1; i <= poz-2; ++i) {
		if (el[i] > mx2) {
			mx2 = el[i];
		}
 		if (mx2 + el[i+1] + mx < rez) {
//			cerr << mx2 << "#" << el[i+1] << "#" << mx << "\n";
	    	rez = mx2 + el[i+1] + mx;
			first = i;
			second = i+1;
		}
	}
	return ;
}

int first_sol (bool afisare) {
	rez = el[1] + el[n];
	int mx = -INF;
	for (int i = 2; i < n; ++i)
		if (mx < el[i])
			mx = el[i];
	rez += mx;
	first = 1;
	second = n-1;
	solve();
	reverse (el+1, el+n+1);
    solve();
	reverse (el+1, el+n+1);
    if (afisare) 
		cerr << rez << "\n" << first << " " << second << "\n";
	return rez;
}

int main() {
	const int max_n = 100;
	const int val_range = 500;
	const int val_start = -205;
	int t;
//	cin >> t;
	t = 100000;
	srand(time(NULL));
	for (int T = 0; T < t; ++T) {
		n = max_n;
		for (int i = 1; i <=n; ++i)
			el[i] = (rand()%val_range) + val_start;
		if (first_sol(0) == second_sol(0)) {
			cerr << "Test " << T << " Accepted\n";
		} else {
	    	cerr << "Test " << T << " Failed\n";
			cerr << n << "\n";
			for (int i = 1; i <=n; ++i)
				cerr << el[i] << " # ";
			cerr << "\n\n";
			first_sol(1);
			second_sol(1);
			return 0;
		}
	}
}
