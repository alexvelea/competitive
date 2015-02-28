#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int inf = 0x3f3f3f3f;

int main() {
	int n, el[105], nr_rez = 0, rez[105];
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	sort (el + 1, el + n + 1);
 	for (int i = 1; i <= n; ++i) {
		int poz = -1, mx = 0;
		for (int j = 1; j <= nr_rez; ++j) {
			if (el[i] >= rez[j] and rez[j] > mx) {
		   		mx = rez[j];
				poz = j;
			} 
		}
		if (poz == -1) {
			++nr_rez;
			rez[nr_rez] = 1;
		} else {
			rez[poz]++;
		}
	}
	cout << nr_rez << '\n';
	return 0;
}
