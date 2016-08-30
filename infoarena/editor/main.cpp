#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream fin("editor.in");
ofstream fout("editor.out");

map<pair<char, char>, bool> pairedOk = {
	{{'[', ']'}, true},
	{{'(', ')'}, true}
};

int main() {
	int t; fin >> t;
	for (int i = 1; i <= t; i += 1) {
		string init; fin >> init;

		vector<char> txt;
		stack<char> st;

		for (char itr : init) {
			if (itr == '*') {
				if (txt.size()) {
					txt.pop_back();
				}
			} else if (itr != 'E') {
				txt.push_back(itr);
			}
		}

		for (char itr : txt) {
			if (st.size() and pairedOk[{st.top(), itr}]) {
				st.pop();
			} else {
				st.push(itr);
			}
		}

		if (st.size() == 0) {
			fout << ":)\n";
		} else {
			fout << ":(\n";
		}
	}
	return 0;
}