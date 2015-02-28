#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("kss.in");
ofstream out("kss.out");

string rez, txt;
int ap[26];

bool bigger(int64 a, int64 b, int64 c) {
	// a * b <= c -> true
	if (a - 5 >= c / b)
		return false;
	if (a * b > c)
		return true;
	return false;
}

int64 get_number(int ind, int64 k) {
	k++;
	int64 rez = 1;
	for (; ind < 26; ++ind) {
		if (bigger(rez, ap[ind] + 1, k))
			return -1;
		rez *= 1LL * (ap[ind] + 1);
	}
	if (rez <= k)
		return rez;
	return -1;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		int64 k;
		in >> n >> k;
 		in >> txt;
		rez.clear();
		for (int i = 0; i < 26; ++i)
			ap[i] = 0;
		for (int i = 0; i < n; ++i)
			ap[txt[i] - 'a']++;
		for (int i = 0; i < 26; ++i)
			if (ap[i])
				cerr << char(i + 'a') << '\t' << ap[i] << '\n';
		if (get_number(0, k) != -1)
			out << "-1\n";
		else {
			for (int i = 0; i < 26; ++i) {
				if (k <= ap[i]) {
					for (int j = 1; j <= k; ++j)
						rez += char('a' + i);
					break;
				}
				k -= ap[i];
				for (int a = ap[i]; a; --a) {
					cerr << i << '\t' << a << '\t' << get_number(i + 1, k) << '\n';
					if (get_number(i + 1, k) == -1) {
						for (int j = 1; j <= a; ++j)
							rez += char('a' + i);
						break;
					} else {
						k -= get_number(i + 1, k) - 1;
					}
				}
			}
			out << rez << '\n';
		}
	}
    return 0;
}
