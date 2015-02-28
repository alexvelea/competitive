#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int max_n = 30005;

const int INF = 0x3f3f3f3f;

ifstream in("secv7.in");
ofstream out("secv7.out");

int n;
int el[max_n];

int rez, first, second;
int rev = 0;

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
	    	rez = mx2 + el[i+1] + mx;
			if (rev == 0) {
				first = i;
				second = i+1;
			} else {
				first = n - (i+1);
				second = n - (i);
			}
		}
	}
	return ;
}

int main() {
 	in >> n;
	for (int i = 1; i <= n; ++i) 
		in >> el[i];
	rez = el[1] + el[n];
	int mx = -INF;
	for (int i = 2; i < n; ++i)
		if (mx < el[i])
			mx = el[i];
	rez += mx;
	first = 1;
	second = n-1;

	solve();
	rev ^= 1;
	reverse (el+1, el+n+1);
    solve();
	reverse (el+1, el+n+1);
	rev ^= 1;
	
	int s = 0;
	mx = -INF;
	for (int i = 1; i <= first; ++i) 
		if (mx < el[i])
			mx = el[i];
	s += mx;

 	mx = -INF;
	for (int i = first+1; i <= second; ++i)
		if (mx < el[i])
			mx = el[i];
	s += mx;
	mx = -INF;
	for (int i = second+1; i <= n; ++i)
		if (mx < el[i])
			mx = el[i];
	s += mx;

	assert (s==rez);

	out << rez << "\n" << first << " " << second << "\n";
	return 0;
}
