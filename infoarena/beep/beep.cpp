#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("beep.in");
ofstream out("beep.out");

string txt, be;

int main() {
 	in >> be;
	bool first = true;
  	while (in >> txt) {
		if (not first)
			out << ' ';
		first = false;
		if (txt == be)
			out << "beep";
		else
			out << txt;
	}
	return 0;
}
