#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMod = 1e9 + 7, kMaxN = 1e3 + 5;

ifstream fin("taxi2.in");
ofstream fout("taxi2.out");

struct Edge {
	int a, b, c;
	int other(int nod) {
		return a + b - nod;
	}
} edge[kMaxN];

int fact[kMaxN];
vector<int> vertex[kMaxN];
int dpSum[2 * kMaxN];
int comb[kMaxN][kMaxN];
bool viz[kMaxN];

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * rez * a) % kMod;
		}
		p /= 2;
		a = (1LL * a * a) % kMod;
	}
	return rez;
}

int df(int nod) {
	int rez = 1;
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (not viz[edge[itr].other(nod)]) {
			rez += df(edge[itr].other(nod));
		}
	}
	viz[nod] = false;
	return rez;
}

int P[kMaxN][2 * kMaxN];

int main() {
	int n, people; fin >> n >> people;
	for (int i = 1; i < n; i += 1) {
		fin >> edge[i].a >> edge[i].b >> edge[i].c;
		vertex[edge[i].a].push_back(i);
		vertex[edge[i].b].push_back(i);
	}

	fact[0] = fact[1] = 1;
	for (int i = 2; i < kMaxN; i += 1) {
		fact[i] = (1LL * fact[i - 1] * i) % kMod;
	}

	comb[1][1] = 1;

	for (int i = 0; i < kMaxN; i += 1) {
		comb[i][0] = comb[0][i] = 1;
	}

	for (int i = 2; i < kMaxN; i += 1) {
		for (int j = 1; j <= i; j += 1) {
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
			if (comb[i][j] >= kMod) {
				comb[i][j] -= kMod;
			}
		}
	}


	for (int a = 0; a <= people; a += 1) {
		for (int b = 0; b <= people; b += 1) {
			int actualSum = (min(a, people - b) + min(b, people - a));
			actualSum = (1LL * actualSum * comb[people][a]) % kMod;
			actualSum = (1LL * actualSum * comb[people][b]) % kMod;
			dpSum[a + b] = (dpSum[a + b] + actualSum) % kMod;
		}
	}

	int rez = 0;

	for (int i = 0; i < kMaxN; i += 1) {
		P[i][0] = 1;
		for (int j = 1; j < 2 * kMaxN; j += 1) {
			P[i][j] = (1LL * P[i][j - 1] * i) % kMod;
		}
	}

	for (int i = 1; i < n; i += 1) {
		viz[edge[i].b] = true;
		int up = df(edge[i].a), down = n - up;
		viz[edge[i].b] = false;

		for (int s = 1; s <= 2 * people; s += 1) {
			int actualSum = edge[i].c;
			actualSum = (1LL * actualSum * P[up][s]) % kMod;
			actualSum = (1LL * actualSum * P[down][2 * people - s]) % kMod;
			actualSum = (1LL * actualSum * dpSum[s]) % kMod;
			// cerr << actualSum << '\n';
			rez += actualSum;
			if (rez >= kMod) {
				rez -= kMod;
			}
		}
	}

	fout << rez << '\n';
	return 0;
}