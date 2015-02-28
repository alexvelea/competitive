#include <iostream>
#include <vector>
using namespace std;

int el[100005];
vector<int> after[1005];

int main() {
	int n, mx = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
		if (el[i] > mx)
			mx = el[i];
	}
 	int rez = mx;
	for (int i = 1; i <= n; ++i) {
		int c = el[i];
		while (c < mx) {
			c *= 2;
			rez++;
		}
	}
 	cout << rez << '\n';        
	if (rez <= 1000) {
		for (int i = 1; i <= n; ++i) {
			while (2 * el[i] < mx) {
				cout << "science mission to the planet " << i << '\n';
				el[i] *= 2;
			}
			after[2 * el[i] - mx].push_back(i);
		}
		for (int i = 0; i < mx; ++i) {
	    	for (int j = 0; j < after[i].size(); ++j)
				cout << "science mission to the planet " << after[i][j] << '\n';
			cout << "flying mission\n";
		}
	}
	
	return 0;
}
