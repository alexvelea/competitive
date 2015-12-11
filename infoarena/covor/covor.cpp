//Problem covor from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 2005;

ifstream in("covor.in");
ofstream out("covor.out");

char el[kMaxN][kMaxN];
int up[kMaxN];

stack<pair<int, int> > Q;

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			in >> el[i][j];
	
    int64 rez = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) 
			if (el[i][j] == '0')
				up[j]++;
			else
				up[j] = 0;

		int sum = 0;

		for (int j = 1; j <= n; ++j) {
			int el = up[j];
			int ap = 1;
			while (Q.size() and Q.top().first >= el) {
				sum -= Q.top().first * Q.top().second;
				ap += Q.top().second;
				Q.pop();
			}
			sum += el * ap;
			Q.push(make_pair(el, ap));
			rez += sum;
		}
		while (Q.size())
			Q.pop();
	}
	out << rez << '\n';
	return 0;
}
