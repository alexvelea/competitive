#include <iostream>
using namespace std;

int Mod;
int l[1000], c[1000];
int rez[1000][1000];

void mod(int &a) {
	if (a >= Mod)
		a -= Mod;
}

int main() {
	bool ok = true;
	int n, m;
	cin >> n >> m >> Mod;
	for (int i = 1; i <= m; ++i) 
		for (int j = 1; j <= n; ++j) {
			char a;
			cin >> a;
			if (a == '1') {
				l[i]++;
				c[j]++;
			}
		}
	int a = 0, b = 0;
	for (int i = 1; i <= n; ++i) {
		if (l[i] != 2 and i <= m)
			ok = false;
		if (c[i] > 2)
			ok = false;
		if (c[i] == 0)
			b++;
		if (c[i] == 1)
			a++;
	}
	if (ok == false) {
		cout << "0\n";
		return 0;
	}
 	rez[a][b] = 1;
	for (int i = 2 * n - 2 * m; i; i -= 2) {
		for (int a = 0, b = i / 2; a <= i; a += 2, b--) {
			if (a != 0 and b != 0) {
				rez[a][b - 1] += (1LL * ((1LL * rez[a][b] * a) % Mod) * b) % Mod;
				mod(rez[a][b - 1]);
			}
			if (a >= 2) {
				if (a % 2 == 0)
					rez[a - 2][b] += (1LL * ((1LL * rez[a][b] * (a / 2)) % Mod) * (a - 1)) % Mod; 
				else
 					rez[a - 2][b] += (1LL * ((1LL * rez[a][b] * a) % Mod) * ((a - 1) / 2)) % Mod;    				
				mod(rez[a - 2][b]);
			}
			if (b >= 2) {
				if (b % 2 == 0)
					rez[a + 2][b - 2] += (1LL * ((1LL * rez[a][b] * (b / 2)) % Mod) * (b - 1)) % Mod; 
				else
 					rez[a + 2][b - 2] += (1LL * ((1LL * rez[a][b] * (b)) % Mod) * ((b - 1) / 2)) % Mod;    				
				mod(rez[a + 2][b - 2]);
			}
		}
	}
	cout << rez[0][0] << '\n';
	return 0;
}
