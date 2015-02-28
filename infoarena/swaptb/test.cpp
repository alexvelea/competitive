#include <iostream>
using namespace std;

struct ABC {
	int el[10][10];
	ABC() {
		for (int j = 0; j < 10; ++j)
		for (int i = 0; i < 10; ++i)
			el[j][i] = j * 10 + j;
	}
	ABC* operator [] (int x) {
		return el[x];
	}
} P;

int main() {
	cout << P[3][3];
	return 0;
}
