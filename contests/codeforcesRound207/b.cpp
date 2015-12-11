#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define ll long long

string a, b;
bool viz[1000005];
int ap[26];
vector<int> id;

int gcd (int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	ll p, q;
 	cin >> p >> q;
	cin >> a >> b;
	if (a.size() > b.size()) {
		swap(a, b);
		swap(q, p);
	}
	int n = a.size();
	int m = b.size();
	ll rez = 0;
	for (int i = 0; i < m; ++i) 
		if (not viz[i]) {
			for (int j = 0; j < 26; ++j)
				ap[j] = 0;
			int ind = i, nr = 0;
			id.clear();
			while (viz[ind] == false) {
				viz[ind] = true;
				ap[b[ind] - 'a'] ++;
				ind += n;
				ind %= m;
				id.push_back(ind);
				++nr;
			}
			for (int ind = 0; ind <int(id.size()); ++ind)
				if (id[ind] < n) {
					rez += 1LL * nr - ap[a[id[ind]] - 'a'];
				}
		}
	ll multi = 1LL * n * m / gcd(n, m);
	rez *= 1LL * n * p / multi;
	cout << rez << '\n';
	return 0;
}
