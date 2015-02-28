#include <fstream>
#include <iostream>
using namespace std;

ifstream in("secv7.in");
ofstream out("secv7.out");

const int max_n = 30005;
const int INF = 0x3f3f3f3f;
int el[max_n];
int n;

int main() {
	int st, dr;
	int rez = INF;
	in >> n;
	for (int i = 1; i <= n; ++i) 
		in >> el[i];
	for (int i = 1; i <n; ++i) 
		for (int j = i+1; j < n; ++j) {
			int s = 0;
			int mx = -INF;
			for (int l = 1; l <= i; ++l)
				if (el[l] > mx)
					mx = el[l];
			s += mx;
			mx = -INF;
 			for (int l = i+1; l <=j; ++l)
				if (el[l] > mx )
					mx = el[l];
			s += mx;
			mx = -INF;
 			for (int l = j+1; l <= n; ++l) 
				if (el[l] > mx)
					mx = el[l];
			s += mx;
			if (rez > s) {
				rez = s;
 				st = i;
				dr = j;
			}
		}
	cerr << rez << "\n";
	return 0;
}


