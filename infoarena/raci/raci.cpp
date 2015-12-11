//Problem raci from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 500005;

ifstream in("raci.in");
ofstream out("raci.out");

char txt[kMaxN][11];
int rez[kMaxN];

deque<int> End[26];

int main() {
	int n, k;
	in >> n >> k;
	for (int i = 1; i <= n; ++i) 
		in >> txt[i];

	for (int i = 1; i <= n; ++i) {
		int ind = txt[i][0] - 'a';
		while (End[ind].size() != 0 and i - End[ind].front() > k)
			End[ind].pop_front();
		int r = 0;
		if (End[ind].size())
			r = rez[End[ind].front()];
		rez[i] = r + 1;
		ind = txt[i][strlen(txt[i]) - 1] - 'a';
		while (End[ind].size() and rez[End[ind].back()] <= rez[i])
			End[ind].pop_back();
		End[ind].push_back(i);
	}

	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		if (rez[i] > mx)
			mx = rez[i];
	}
	out << mx << '\n';
	return 0;
}
