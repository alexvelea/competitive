#include <fstream>
#include <iostream>
using namespace std;
int main() {
	ifstream in("xerox.in");
	ofstream out("xerox.out");
 	int T;
	in >> T;
	while (T--) {
		int n, rez = 0;
		in >> n;
		int a, b, el;
		in >> a >> b;
		while (n--) {
			in >> el;
			rez ^= el;
			while (el--)
				in >> a >> b;
		}
		out << ((rez != 0)?(1):(0)) << '\n';
	}
	return 0;
}
