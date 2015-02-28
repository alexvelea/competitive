#include <iostream>
using namespace std;
int main() {
	int mx = 0, nr = 0;
	for (int i = 1; i <= 65520; ++i) {
		if (65520 % i == 0)
			++mx;
	}
	cout << mx << '\t' << nr << '\n';
}
