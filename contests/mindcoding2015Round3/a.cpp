//Problem a from mingcoding2015Round3
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
 	char txt[500];
	while (cin.getline(txt, 500)) {
 		int itr = 0;
		int rez = 0, exp = 0;
	   	if (txt[0] == 'u') {
			itr += 8;
		}
		
		while (txt[itr] == ' ')
			++itr;
		
		if (txt[itr] == 'c') {
			exp = 1;
		} else if (txt[itr] == 'i') {
			exp = 4;
		} else {
			exp = 2;
		}

		while (txt[itr] != ' ')
			++itr;

		while (itr < int(strlen(txt))) {
			int m = 1;
    	    
 			while (itr < int(strlen(txt)) and txt[itr] != '[' and txt[itr] != ',')
				++itr;
		
			while (itr < int(strlen(txt)) and txt[itr] == '[') {
				int aux = 0;
				++itr;
				while (itr < int(strlen(txt)) and txt[itr] != ']' and txt[itr] != ',') {
					aux *= 10;
					aux += txt[itr] - '0';
					++itr;
				}
				itr++;
				m *= aux;
			}

			rez += m;
			if (itr == int(strlen(txt)))
				break;
			
			while (txt[itr] == ',' or txt[itr] == ' ') {
				++itr;
			}
		}


		cout << rez * exp;
	}
	return 0;
}
