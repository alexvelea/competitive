#include <string>
#include <iostream>
using namespace std;

std::string lineEncoding(std::string s) {
  	s += '#';
  	std::string rez = "";
  	int a = 0;
	for (int i = int(s.size()) - 1; i >= 0; --i) {
		if (i == 0 or s[i] != s[i - 1]) {
 			rez += s[i];   		
			while (a) {
				rez += a % 10;
				a /= 10;
			}
			a = 0;
		} else {
			++a;
		}
	}
	std::reverse(rez.begin(), rez.end());
	return rez;
}

int main() {
	std::string x = "aaabbb";
	std::cout << lineEncoding(x) << '\n';
	return 0;
}
