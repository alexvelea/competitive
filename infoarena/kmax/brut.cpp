#include <fstream>
#include <iostream>
using namespace std;

ifstream in("kmax.in");

int N, K, Mod;
int rez;

int viz[25], el[25];

void bt(int ind, int k) {
	if (k == K + 1)
		return ;
	if (ind == N + 1) {
		rez++;
		if (rez == Mod)
			rez = 0;
		return ;
	}
	for (int i = 1; i <= N; ++i)
		if (not viz[i]) {
			viz[i] = true;
			el[ind] = i;
			if (el[ind - 1] > i)
				bt(ind + 1, 1);
			else
				bt(ind + 1, k + 1);
			viz[i] = false;
		}
}

int main() {
	in >> N >> K >> Mod;
	bt(1, 0);
	cerr << rez << '\n';
	return 0;
}
