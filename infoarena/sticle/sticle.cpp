#include <fstream>
using namespace std;
ifstream in("sticle.in");
ofstream out("sticle.out");
int main() {
	int t;
	in >> t;
	while (t--) {
		int x, rez = 0;
		in >> x;
		x --;
		while (x) {
			rez ++;
			x >>= 1;
		}
		out << rez << '\n';
	}
}

