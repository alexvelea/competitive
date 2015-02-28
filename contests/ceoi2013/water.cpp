#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

char el[3000][3000];

void solve(int x, int y) {
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (el[x + i][y + j] == '#' || el[x+i][y+j] == '$') {
				int s = i * 5 + j;
				char t[20];
				if (s < 10) {
					t[0] = s + '0';
					t[1] = '.';
					t[2] = 't';
					t[3] = 'x';
					t[4] = 't';
					t[5] = '\0';
				} else{
					t[0] = s / 10 + '0';
					t[1] = s % 10 + '0';
					t[2] = '.';
					t[3] = 't';
					t[4] = 'x';
					t[5] = 't';
					t[6] = '\0';
				}               
				ifstream in(t);
				for (int i = 0; i < 5; ++i)
					for (int j = 0; j < 5; ++j) 
						in >> el[x+i][y+j];
				return ;
			}
}

int main() {
	int r, c;
	ifstream fin("watering.in.5");
	ofstream out("watering.out");
	fin >> r >> c;
 	for (int i = 1; i <= 6 * r - 1; ++i)
		for (int j = 1; j <= 6 * c - 1; ++j)
			fin >> el[i][j];
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			solve((i - 1) * 6 + 1, (j - 1) * 6 + 1);
	for (int i = 1; i <= 6 * r - 1; ++i, out << '\n')
		for (int j = 1; j <= 6 * c - 1; ++j)
			out << el[i][j];
	return 0;
}
