#include <fstream>
#include <iostream>
using namespace std;

const int max_n = 1005;
const int MOD = 1000000;

ifstream in("sir23.in");
ofstream out("sir23.out");

int n;
int S[max_n][max_n], Sum[max_n][max_n];

void mod (int &a) {
	while (a >= MOD) {
		a -= MOD;
	}
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i) {
   		S[1][i] = i;
		S[2][i] = i * i;
		mod (S[2][i]);
		for (int j = 1; j <= 2; ++j) {
			Sum[j][i] = Sum[j][i-1] + S[j][i];
			mod (Sum[i][j]);
		}
	} 
	for (int i = 3; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			S[i][j] += S[i][j-1] + S[i-1][j-1];
			mod (S[i][j]);
			S[i][j] += S[i-2][j-1];
			mod (S[i][j]);
			if (j > 2)
				S[i][j] += Sum[i-2][j-2];
			mod (S[i][j]);
			Sum[i][j] = Sum[i][j-1] + S[i][j];
			mod (Sum[i][j]);
		}
	}
	out << S[n][n];
	return 0;
}
