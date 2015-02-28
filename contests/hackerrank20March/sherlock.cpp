#include <cmath>

#include <iostream>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
    	int a, b;
		cin >> a >> b;
		a--;
		cout << int(sqrt(b)) - int(sqrt(a)) << '\n';
	}
	return 0;
}
