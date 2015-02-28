#include <iostream>
using namespace std;
int main() {
	int a, b;
	int rezA = 0, rezB = 0, rezC = 0;
	cin >> a >> b;
		for (int i = 1; i <= 6; ++i) {
			int A = abs(i - a);
			int B = abs(i - b);
			if (A == B)
				rezB++;
			if (A < B)
				rezA++;
			if (A > B)
				rezC++;
		}
	cout << rezA << ' ' << rezB << ' ' << rezC << '\n';
	return 0;
}
