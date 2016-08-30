#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream fin("kfib.in");
ofstream fout("kfib.out");

const int kMod = 666013;

struct Mat {
	int el[2][2];
	Mat() {
		el[0][0] = el[1][1] = 1;
		el[1][0] = el[0][1] = 0;
	}
	Mat inm(Mat a) {
		Mat rez;
		for (int i = 0; i < 2; i += 1) {
			for (int j = 0; j < 2; j += 1) {
				rez.el[i][j] = 0;
				for (int l = 0; l < 2; l += 1) {
					rez.el[i][j] = (rez.el[i][j] + 1LL * el[i][l] * a.el[l][j]) % kMod;
				}
			}
		}
		return rez;
	}
} rez;

Mat pow(int p, Mat x) {
	Mat rez;
	while (p) {
		if (p & 1) {
			rez = rez.inm(x);
		}
		x = x.inm(x);
		p /= 2;
	}
	return rez;
}

int main() {
	rez.el[0][0] = 0;
	rez.el[0][1] = 1;
	rez.el[1][1] = 1;
	rez.el[1][0] = 1;

	int n; fin >> n;
	rez = pow(n - 1, rez);
	fout << rez.el[1][1];
	return 0;
}