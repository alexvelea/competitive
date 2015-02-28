#include <iostream>
using namespace std;

struct aa {
	int v;
	aa() {
		cerr << "ins" << '\n';
	}
	aa(int a) {
		cerr << "ins_n\n";
		v = a;
	}
	~aa() {
		cerr << "del\n";
	}
};

int main() {
	aa x[10];
 	x[4] = aa(4);
	x[3] = aa(3);
	return 0;
}
