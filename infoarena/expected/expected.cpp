//Problem expected from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("expected.in");
ofstream out("expected.out");

int main() {
	int a, b;
	in >> a >> b;
/*	double comb = 1;
	for (int i = a + 1; i <= a + b; ++i)
		comb *= i;
	for (int i = 1; i <= b; ++i)
		comb /= i;*/
	double suma = 0, sumb = 0;
	int T = 100000;
	for (int t = 1; t < T; ++t) {
		// sansa de t / 1000 pt prima chestie
		// de (1000 - t) / 1000 pt a 2-a
		double p = 1.0 * pow(1.0 * t / T, a) * pow((1.0 * T - t) / T, b);
		suma += t * p;
		sumb += p;
	}
	out << suma / sumb / 1.0 / T << '\n';
	return 0;
}
