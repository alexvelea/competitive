//Problem #B from Codeforces code_strike_2014_round_1
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

vector<int> v;

int main() {
 	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		int aux;
		cin >> aux;
		v.push_back(aux);
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	cout << v[k - 1];
    return 0;
}

