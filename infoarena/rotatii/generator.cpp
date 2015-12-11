#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>
using namespace std;
int main() {
	srand(time(NULL));
	const int kMaxVal = 10;
	for (int T = 0; T < 1; ++T) {
		ofstream out("rotatii.in");
		int n = 10, m = 100, inside = 0;
		out << n << ' ' << m << '\n';
		for (int i = 1; i <= n; ++i) {
			int x = rand() % kMaxVal;
			x -= kMaxVal / 2;
			out << x << ' ';
			inside++;
		}
		out << '\n';
		for (int i = 1; i <= m; ++i) {
        	int x = rand() % 10;
			if (x < 2) {
				out << "2\n";
				continue;
			}
			if (x & 1) {
				int poz = rand() % inside + 1;
				out << "1 " << poz << '\n';
				--inside;
			} else {
				int poz = rand() % inside;
				int val = rand() % kMaxVal;
				val -= kMaxVal / 2;
				out << "0 " << poz << ' ' << val << '\n';
				inside++;
			}
		}
		out.close();
		system("./rotatii");
	}
}
