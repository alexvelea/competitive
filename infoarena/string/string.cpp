#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream in("string.in");
ofstream out("string.out");

int n;
bool viz[530000], v[530000];

string t;


int main() {
	in >> n;
	in >> t;
	for (int i = 0; i < n; ++i)
		if (t[i] == 'a')
			v[i] = 0;
		else
			v[i] = 1;
	for (int l = 1; ; ++l) {
		//mark first l
		for (int i = 0; i < (1<<l); ++i)
			viz[i] = false;
		int p = 0, val = 0;
		for (; p < l - 1; ++p) {
			val <<= 1;
			val += v[p];
		}
		for (; p < n; ++p) {
			val <<= 1;
			val &= (1<<l) - 1;
			val += v[p];
			viz[val] = true;
		}
		for (int i = 0; i < (1<<l); ++i) 
			if (viz[i] == false) {
				out << l << "\n";
				for (int j = l-1; j >= 0; --j) {
					if (i & (1<<j))
						out << 'b';
					else
						out << 'a';
				}
				return 0;
			}
	}
	return 0;
}
