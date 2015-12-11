#include <cassert>

#include <fstream>
#include <iostream>
using namespace std;

const int kMaxM = 200005, kMaxN = 105, kMaxL = 5005;

ifstream in("search.in");
ofstream out("search.out");

string txt[kMaxN];
char op[kMaxM];

int next_char[26][kMaxL];
int el[kMaxM], m, rez[kMaxM];

void solve(int ind) {
	int n = txt[ind].size();
	for (int j = 0; j < 26; ++j) {
		next_char[j][n - 1] = n;
		next_char[j][n] = n;
	}
	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j < 26; ++j)
			next_char[j][i] = next_char[j][i + 1];
		next_char[txt[ind][i + 1] - 'a'][i] = i + 1;
	}
	int st = 0;
	for (int i = 1; i <= m; ++i) {
		if (op[i] == '-') {
			st--;
		} else {
			int ind = op[i] - 'a';
			el[st + 1] = next_char[ind][el[st]];
			st++;
		}
		if (el[st] < n)
			rez[i]++;
	}
}	

int main() {
	int n;
	in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		in >> txt[0];
		txt[i] = '#';
		txt[i] += txt[0];
	}
	for (int i = 1; i <= m; ++i)
		in >> op[i];

	for (int i = 1; i <= n; ++i)
		solve(i);
	
	for (int i = 1; i <= m; ++i)
		out << rez[i] << '\n';
    return 0;
}
