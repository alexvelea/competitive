#include <iostream>
#include <fstream>
using namespace std;

int main() {
	int n;
	while (cin >> n)
		if ((n % 3 == 1) || (n % 3 == 2))
			cout << 1 << '\n';
		else
			cout << '0' << '\n';
	return 0;
}
