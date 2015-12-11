#include <fstream>
#include <iostream>
using namespace std;

const int inf = 0x3f3f3f3f;
int x[10000], y[10000], viz[10000][3];

int n, m;

void insert(int ind) {
	int mx = 0, act;
	int c1, c2;
	for (int i = 1; i<= n; ++i)
		for (int j = 1; j <= 2; ++j) {
			act = inf;
 			for (int l = 1; l <= n; ++l)
				for (int c = 1; c <= 2; ++c) {
					if (viz[l][c])
 						if (act > (l-i) * (l-i) + (c-j) * (c-j))
							act = (l-i) * (l-i) + (c-j) * (c-j);
				}
			if (act > mx) {
				mx = act;
				c1 = i;
				c2 = j;
			}
		}
	x[ind] = c1;
	y[ind] = c2;
	viz[c1][c2] = true;
}

void erase(int ind) {
	if (viz[x[ind]][y[ind]] == false)
		cout << "BAD";
	viz[x[ind]][y[ind]] = false;
}

int main() {
	ifstream in("tram.in");
	ofstream out("tram2.out");
	int a = 0;
 	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		char type;
		in >> type;
		if (type == 'E') {
			insert(i);
			out << x[i] << ' ' << y[i] << '\n';
			++a;
		} else {
			int ind;
			in >> ind;
			erase(ind);
		}
	}
	return 0;
}
