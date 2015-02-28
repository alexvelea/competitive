#include <fstream>
#include <iostream>
#include <string>
using namespace std;
ifstream in("soldati.in");
ofstream out("soldati.out");

int main() {
	int T;
	in >> T;
	while (T--) {
		string str;
		in >> str;
		int itr = 0;
		int delay = 0, left = 0, mx = 0;
        while (itr < int(str.size()) and str[itr] == '<') {
			++itr;
		}

		for (; itr < int(str.size()); ++itr) {
			if (itr > 0 and str[itr] == '<' and str[itr - 1] == '<') {
				++delay;
			}
			if (itr > 0 and str[itr] == '>' and str[itr - 1] == '>') {
				--delay;
         	}
			if (str[itr] == '>')
				++left;
			if (delay < 0) {
				delay = 0;
			}
			if (str[itr] == '<') {
				mx = max(mx, delay + left);
			}
		}

		out << mx << '\n';
	}
	return 0;
}
