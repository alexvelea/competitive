#include <iostream>
#include <fstream>
using namespace std;

int main() {

		ifstream a_in("kami.out");
		ifstream b_in("kami2.out");
		long long x = 0, y = 0;
		while (a_in >> x) {
			b_in >> y;
			if (x != y) {
				cerr << "Bad!BAD  BAD   BAD";
				break;
			}
		}
		cerr << '\n';
    
	return 0;
}
