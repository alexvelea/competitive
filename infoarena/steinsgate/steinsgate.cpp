#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 205;

ifstream fin("steinsgate.in");
ofstream fout("steinsgate.out");

struct Matrix {
	bool cell[kMaxN][kMaxN];

	Matrix() {
		for (int i = 0; i < kMaxN; i += 1) {
			for (int j = 0; j < kMaxN; j += 1) {
				this->cell[i][i] = false;
			}

			this->cell[i][i] = true;
		}
	}

	Matrix operator * (const Matrix &rhs) const {
		Matrix final;
		for (int i = 0; i < kMaxN; i += 1) {
			for (int j = 0; j < kMaxN; j += 1) {
				final.cell[i][j] = 0;
				for (int l = 0; l < kMaxN and not final.cell[i][j]; l += 1) {
					final.cell[i][j] |= this->cell[i][l] & rhs.cell[l][j];
				}
			}
		}
		return final;
	}
} initial_matrix;

Matrix pow(Matrix a, int p) {
	Matrix rez;
	while (p) {
		if (p & 1) {
			rez = rez * a;
		}

		a = a * a;
		p /= 2;
	}

	return rez;
}

int initial_cost[kMaxN];
int best_cost[kMaxN];

int main() {
	int n, m, k; fin >> n >> m >> k;
	for (int i = 1; i <= n; i += 1) {
		initial_matrix.cell[i][i] = false;
	}
	for (int i = 1; i <= m; i += 1) {
		int x, y; fin >> x >> y;
		initial_matrix.cell[x][y] = true;
	}

	initial_matrix = pow(initial_matrix, k);
	for (int i = 1; i <= n; i += 1) {
		fin >> initial_cost[i];
	}

	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= n; j += 1) {
			if (initial_matrix.cell[i][j]) {
				best_cost[j] = max(best_cost[j], initial_cost[i]);
			}
		}
	}

	for (int i = 1; i <= n; i += 1) {
		fout << best_cost[i] << ' ';
	}

	return 0;
}