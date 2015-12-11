//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

const int Mod = 666013;

ifstream in("android.in");
ofstream out("android.out");

int gcd(int a, int b) {
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	return gcd(b, a % b);
}

int poz[2][20 * 20], nr_poz;
int n, m;

int rez[20][(1 << 20)];

int dx[4] = {1, 1, -1, -1};
int dy[4] = {-1, 1, -1, 1};

bool inside(int x, int y) {
	if (x < 0 or y < 0 or x >= n or y >= m)
		return false;
	return true;
}

void mod(int &a) {
	if (a >= Mod)
		a -= Mod;
}

int main() {
	in >> n >> m;
	poz[0][1] = 1;
	poz[0][2] = -1;
	poz[1][3] = 1;
	poz[1][4] = -1;
	nr_poz = 4;
	for (int i = 1; i < n; ++i)
		for (int j = 1; j < m; ++j)
			if (gcd(i, j) == 1) {
				for (int d = 0; d < 4; ++d) {
					++nr_poz;
					poz[0][nr_poz] = i * dx[d];
					poz[1][nr_poz] = j * dy[d];
				}
			}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			rez[i * m + j][1 << (i * m + j)] = 1;
	int r = 0;
	for (int st = 0; st < (1 << (n * m)); ++st)
		for (int nod = 0; nod < n * m; ++nod)
			if (st & (1 << nod) and rez[nod][st]) {
				r += rez[nod][st];
				mod(r);

					for (int i = 1; i <= nr_poz; ++i) {
						int Dx = poz[0][i];
						int Dy = poz[1][i];
						int x = nod / m, y = nod % m;
                        while (inside(x, y) and (st & (1 << (x * m + y)))) {
							x += Dx;
							y += Dy;
						}

						if (inside(x, y) == true) {
							rez[x * m + y][st | (1 << (x * m + y))] += rez[nod][st];
							mod(rez[x * m + y][st | (1 << (x * m + y))]);
						}
					}
			}
	out << r << '\n';
    return 0;
}
