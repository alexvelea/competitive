//Problem A from Codeforces Round 282
// "We are drowning in information and starved for knowledge."

/* VIVA LA PERU
SMASH ES MI PASTOR */

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

string x;

int main() {
	int poz = -1;
	cin >> x;
 	for (int i = x.size() - 1; i >= 0 and poz == -1; --i)
		if (x[i] == '#')
			poz = i;
	
	int sum = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (x[i] == '(') 
			sum++;
		if (x[i] == ')' || x[i] == '#')
			sum--;
	}
 	bool ok = true;
	if (sum < 0)
		ok = false;
	int rez = sum;
	sum = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (x[i] == '(')
			sum++;
		if (x[i] == ')' || x[i] == '#')
			sum--;
		if (i == poz)
			sum -= rez;
		if (sum < 0)
			ok = false;
	}
	if (sum != 0)
		ok = false;
	if (ok == false) {
		cout << -1;
	} else {
		for (int i = 0; i != poz; ++i)
			if (x[i] == '#')
			cout << 1 << ' ';
		cout << rez + 1 << '\n';
	}
	return 0;

}
