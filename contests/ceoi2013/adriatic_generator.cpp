#include <iostream>
#include <fstream>
using namespace std;
bool viz[2505][2505];
int main() {
	int n = (rand() % 200) + 200;
	int mod = (rand() % 1000) + 1000;
	ofstream out("adriatic.in");

		out << n << '\n';
		for (int i = 1; i <= n; ++i) {
			int x, y;
			x = rand() % mod;
			y = rand() % mod;
			x++;
			y++;
			if (viz[x][y])
				--i;
			else {
				viz[x][y] = true;
				out << x << ' ' << y << '\n';
			}
		}
}

