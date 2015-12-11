#include <iostream>
using namespace std;

int main() {
	long long a  = 0;
	int c = 1000000;
	for (int i = 0; i <= 1000000; ++i)
		a += c;
	cout << a << '\n';
}
