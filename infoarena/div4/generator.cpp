#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	srand(time(NULL));
	ofstream out("div4.in");
	int n = 10000;
	for (int i = 0; i < n; ++i) {
    	int x = rand() % 9;
		x++;
		out << char(x + '0');
	}
	out << '\n';
	out << rand() % n + 1 << '\n';
}
