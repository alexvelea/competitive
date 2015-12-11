//Problem logs from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 15005, kMaxM = 1505;

ifstream in("logs.in");
ofstream out("logs.out");

char el[kMaxN][kMaxM];
int sum[kMaxM], srt[kMaxM];

const int mx = 50;
int el_ap[mx], mx_el[kMaxM];

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 0; i < n; ++i)
		in >> el[i];
	int rez = 0;
	for (int i = 0; i < n; ++i) {
		mx_el[0] = 0;
		for (int j = 0; j < m; ++j) 
			if (el[i][j] == '0') {
				sum[j] = 0;
			} else {
				sum[j]++;
				if (sum[j] < mx)
					el_ap[sum[j]]++;
				if (sum[j] == mx) {
					mx_el[++mx_el[0]] = j;
				}
			}
		int c = srt[0];
		srt[0] = 0;
		for (int j = 1; j <= c; ++j)
			if (sum[srt[j]] > mx)
				srt[++srt[0]] = srt[j];
		for (int j = 1; j <= mx_el[0]; ++j)
			srt[++srt[0]] = mx_el[j];
		for (int j = srt[0]; j; --j)
			rez = max(rez, j * sum[srt[j]]);
		for (int j = mx - 1; j; --j) {
			rez = max(rez, j * (srt[0] + el_ap[j]));
			el_ap[j - 1] += el_ap[j];
			el_ap[j] = 0;
		}
	}
	out << rez << '\n';
	return 0;
}
