#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream fin("data.txt");
#include "parser.cpp"

int main() {
	int n; fin >> n;
	int64 rez = 0;
	for (int i = 1; i <= n; i += 1) {
		int x; readNumber(x);
		rez += x;
	}
	cout << rez << '\n';
	return 0;
}