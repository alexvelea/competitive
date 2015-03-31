//Problem c from codeforcesRound297
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int el[100005];

int main() {
	int64 rez = 0;
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
	}
	sort(el + 1, el + n + 1);
	reverse(el + 1, el + n + 1);
	vector<int> aux;
	for (int i = 1; i < n; ++i) {
		if (abs(el[i] - el[i + 1]) <= 1) {
			aux.push_back(el[i + 1]);
			i++;	
		}
	}
	for (int i = 0; i + 1< int(aux.size()); i += 2) {
		rez += 1LL * aux[i] * aux[i + 1];
	}
	cout << rez << '\n';
	return 0;
}
