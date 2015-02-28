#include <iostream>
using namespace std;

int cross(int x, int y, int a, int b) {
	return x * a - y * b;
}

int main() {
 	while (1) {
		int x, y, a, b;
		cout << "!!!!!!\n";
		cin >> x >> y >> a >> b;
		cout << cross(x, y, a, b) << '\n';
	}
}
