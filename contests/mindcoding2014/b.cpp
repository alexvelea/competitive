//Problem #B from Codeforces mindcode
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

int tax[4][7];
int nr;

void solve(int ind) {
	double t[7] = {0.1, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396};
	for (int i = 6; i >= 0; --i) {
		if (tax[ind][i] <= nr) {
			cout << int(1.0 * t[i] * nr) << '\n';
			return ;
		}
	}
}

int main() {
	tax[0][0] = 0;
	tax[0][1] = 9075;
	tax[0][2] = 36900;
	tax[0][3] = 89350;
	tax[0][4] = 186350;
	tax[0][5] = 405100;
	tax[0][6] = 406750;
    
	tax[1][0] = 0;
	tax[1][1] = 18150;
	tax[1][2] = 73800;
	tax[1][3] = 148850;
	tax[1][4] = 226850;
	tax[1][5] = 405100;
	tax[1][6] = 457600;

	tax[2][0] = 0;
	tax[2][1] = 12950;
	tax[2][2] = 49400;
	tax[2][3] = 127550;
	tax[2][4] = 206600;
	tax[2][5] = 405100;
	tax[2][6] = 432200;

	tax[3][0] = 0;
	tax[3][1] = 9075;
	tax[3][2] = 36900;
	tax[3][3] = 74425;
	tax[3][4] = 113425;
	tax[3][5] = 202550;
	tax[3][6] = 228800;

	char txt[200];
	cin.getline(txt, 200);
	cin >> nr;

	int ind = 0;
	if (txt[1] == 'i') {
		ind = 0;
		solve(ind);
		return 0;
	}
	if (txt[1] == 'u')
		ind = 1;
	if (txt[0] == 'H')
		ind = 2;
	if (txt[8] == 'f')
		ind = 3;
	if (txt[8] == 'j')
		ind = 1;
	solve(ind);
	return 0;
}

