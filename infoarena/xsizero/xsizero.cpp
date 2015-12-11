#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

const int tn = 200000;

ifstream in("xsizero.in");
ofstream out("xsizero.out");

// 2 = win
// 1 = draw
// 0 = lose
// -1 = invalid

int viz[tn], sol[tn];

int get_code(int x[3][3]) {
	int rez = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			rez *= 3;
			rez += x[i][j];
		}
	return rez;
}

int unpack(int x[3][3], int c) {
	int nr = 0;
	for (int i = 8; i >= 0; --i) {
 		x[i / 3][i % 3] = c % 3;
		if (c % 3 == 1)
			nr++;
		if (c % 3 == 2)
			nr--;
		c /= 3;
	}
   	return nr;
}

void get_min(int &x, int a) {
	if (x > a)
		x = a;
}

int aux = 0;

int solve(int st) {
//	aux ++;
//	cerr << aux << '\n';

	if (viz[st] == 1)
		return sol[st];
	int x[3][3];
	int nr = 0;
	nr = unpack(x, st);
	if (nr != 0 and nr != 1)
		return -1;
//    for (int i = 0; i < 3; ++i)
//		for (int j = 0; j < 3; ++j)
//			cerr << x[i][j];

	int cx = 0, co = 0;
 	for (int i = 0; i < 3; ++i) {
		if (x[i][0] == x[i][1] and x[i][1] == x[i][2]) {
			if (x[i][0] == 1)
				cx = 1;
			if (x[i][0] == 2)
				co = 1;
		}
		if (x[0][i] == x[1][i] and x[1][i] == x[2][i]) {
			if (x[0][i] == 1)
				cx = 1;
			if (x[0][i] == 2)
				co = 1;
		}
	}
	if (x[0][0] == x[1][1] and x[2][2] == x[1][1]) {
		if (x[0][0] == 1)
			cx = 1;
		if (x[0][0] == 2)
			co = 1;
	}
	if (x[0][2] == x[1][1] and x[1][1] == x[2][0]) {
		if (x[1][1] == 1)
			cx = 1;
		if (x[1][1] == 2)
			co = 1;
	}
	viz[st] = 1;
	if (co and cx)
		return -1;
    if (cx and nr == 0)
 		sol[st] = 2;
	if (cx and nr == 1)
		sol[st] = 0;
	if (co and nr == 1)
		sol[st] = 2;
	if (co and nr == 0)
		sol[st] = 0;
	if (co or cx)
		return sol[st];

	int mn = 4;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (x[i][j] == 0) {
				x[i][j] = nr + 1;
				int aux = solve(get_code(x));
				if (aux == -1)
					assert(0);
				get_min(mn, aux);
				x[i][j] = 0;
			}
	if (mn == 4 or mn == 1)
		sol[st] = 1;
	if (mn == 2)
        sol[st] = 0;
	if (mn == 0)
		sol[st] = 2;
	return sol[st];
}

int main() {
 	solve(0);
	int t = 0;
	char c;
	char el[9];
 	while (in >> c) {
		++t;
		out << "Testul #" << t << ": ";
		el[0] = c;
		for (int i = 1; i < 9; ++i)
			in >> el[i];
		int x[3][3];
 		for (int i = 0; i < 9; ++i) {
			if (el[i] == 'X')
				x[i / 3][i % 3] = 1;
			if (el[i] == '0')
				x[i / 3][i % 3] = 2;
			if (el[i] == '.')
				x[i / 3][i % 3] = 0;
		}
		int st = get_code(x);
		int nr = unpack(x, st);
		int r = solve(st);
		if (nr == 1) {
			// trebuie afisat din perspectiva primului jucator
			// 0 e la mutare acum
			if (r == 2)
				r = 0;
			if (r == 0)
				r = 2;
		}
		if (r == 0)
			out << "lose\n";
		if (r == 1)
			out << "draw\n";
		if (r == 2)
			out << "win\n";
		if (r == -1)
			out << "invalid\n";
	}
	return 0;
}
