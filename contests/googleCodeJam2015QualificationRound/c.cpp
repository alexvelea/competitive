//Problem c from googleCodeJam2015QualificationRound
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream fin("c.in");
ofstream fout("c.out");

map<pair<char, char>, char> switchSign;

pair<char, bool> applyOP(char a, char b) {
	if (a == '1') {
		return {b, false};
	}
	
	if (b == '1') {
		return {a, false};
	}

	if (a == b) {
		return {'1', true};
	}

	return {'i' + 'j' + 'k' - a - b, switchSign[{a, b}]};
}

pair<char, bool> applyOP(pair<char, bool> a, pair<char, bool> b) {
	pair<char, bool> rez = applyOP(a.first, b.first);
	rez.second ^= a.second ^ b.second;
	return rez;
}

int main() {
	ios::sync_with_stdio(false);
	switchSign = { 
 		{{'i', 'k'}, true},
		{{'j', 'i'}, true},
		{{'k', 'j'}, true},
	};

 	int t; fin >> t;
	for (int T = 1; T <= t; ++T) {
		int n; int64 ap; fin >> n >> ap;	    	
		string txt; fin >> txt;

 		pair<char, bool> stringRez = {'1', false}, finalRez = {'1', false};
		for (auto itr : txt) {
			stringRez = applyOP(stringRez, {itr, false});
		}

		int p = ap % 4;
		for (int i = 0; i < p; ++i) {
			finalRez = applyOP(finalRez, stringRez);
		}

		bool ok = true;

		if (finalRez != make_pair('1', true)) {
			ok = false;
		} else {
			// cautam {i, false}
 			string a = txt + txt + txt + txt; // mx 4
			int indA = 0, indB = 0;
			pair<char, bool> rezA = {'1', false}, rezB = {'1', false};
			for (auto itr : a) {
				++indA;
				rezA = applyOP(rezA, {itr, false});
				if (rezA == make_pair('i', false))
					break;
			}
            reverse(a.begin(), a.end());
 			for (auto itr : a) {
				++indB;
				rezB = applyOP({itr, false}, rezB);
				if (rezB == make_pair('k', false))
					break;
			}   		
			if (1LL * n * ap > indA + indB and indA != int(a.size()) and indB != int(a.size())) {
				;
			} else {
				ok = false;
			}
		}

		fout << "Case #" << T << ": " << ((ok) ? ("YES") : ("NO")) << '\n';
	}
	return 0;
}
