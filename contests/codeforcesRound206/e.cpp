#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

int from[23][10][10];
bool good[23][10][10];

int viz[100], id[100];
int nr[3] = {0, 4, 7};

vector<int> el;

int main() {
	for (int i = 0; i <= 728; ++i) {
		int x = i;
		int rez = 0;
		while (x) {
			rez += nr[x % 3];
			x /= 3;
		}
		if (not viz[rez]) {
			el.push_back(rez);
			viz[rez] = true;
			id[rez] = i;
		}
	}
//	FORIT(it, el)
//		cerr << *it << ' ';
	int t;
	cin >> t;
	while (t--) {
		long long x;
		int cif[21];
		cin >> x;
		int i = 1;
		for (int i = 0; i <= 20; ++i)
			cif[i] = 0;
		i = 1;
		do {
			cif[i] = x % 10;
			x /= 10;
			++i;
		} while(x);
 		for (int i = 0; i <= 20; ++i)
			for (int a = 0; a < 10; ++a)
				for (int b = 0; b < 10; ++b) {
 					good[i][a][b] = false;
					from[i][a][b] = 0;
				}
		good[17][0][0] = true;
		for (int i = 18; i; --i) 
			for (int a = 0; a < 10; ++a) 
				for (int b = 0; b < 10; ++b)
					if (good[i][a][b] == true) {
						FORIT(it, el) {
							int c, nb, na;
							c = (*it) % 10;
							nb = b + (*it) / 10;
							na = a + nb / 10;
							nb %= 10;
							if (na > 9)
								continue;
							if (na != cif[i + 2])
								continue;
                         	good[i - 1][nb][c] = true;
							from[i - 1][nb][c] = *it;
						}
					}
		if (not good[0][cif[2]][cif[1]])
			cout << "-1\n";
		else {
			
		}
	}
}
