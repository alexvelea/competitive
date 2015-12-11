//Problem a from codeforcesRound297
//"We are drowning in information and starved for knowledge."
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int key[50];

int main() {
	ios::sync_with_stdio(false);
 	int n; cin >> n;
	string txt; cin >> txt;
	int rez = 0;
	for (int i = 0; i < 2 * (n - 1); i += 2) {
		key[txt[i] - 'a']++;
		key[txt[i + 1] - 'A']--;
		if (key[txt[i + 1] - 'A'] == -1) {
			key[txt[i + 1] - 'A'] = 0;
			++rez;
		}
	}
	cout << rez;
	return 0;
}
