#include <cmath>
#include <iostream>
using namespace std;
int ap[10], act[10];
int main () {
	int n, sum = 0;
 	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		ap[a] ++;
		sum += a;
	}
	ap[0] = n * 10;
	int mx = n * 10;
	for (int i = 0; i <= sum / 3; ++i) {
		int remain = sum - i * 3;
		if (remain % 4 != 0)
			continue;
		int a = i;
		int b = remain / 4;
		for (int j = 0; j <= 4; ++j)
			act[j] = ap[j];
 		int x = min(b, ap[4]);
 		b -= x;
		act[4] -= x;
		x = min(a, ap[3]);
		int j = 4;
		int rez = 0;
		while (b) { 
            int x = min(b, act[j]);
			b -= x;
			act[j] -= x;
			rez += x * max(0, 4 - j);
			--j;
		}
		j = 4;
 		while (a) { 
            int x = min(a, act[j]);
			a -= x;
			act[j] -= x;
			rez += x * max(0, 3 - j);
			--j;
		}        	
		if (rez < mx)
			mx = rez;
	}
	if (mx == n * 10)
		cout << "-1";
	else
		cout << mx << ' ';
	return 0;
}
