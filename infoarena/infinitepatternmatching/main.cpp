#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream fin("infinitepatternmatching.in");
ofstream fout("infinitepatternmatching.out");

string toString(int64 x) {
	string rez = "";
	while (x) {
		rez += char('0' + (x % 2));
		x /= 2;
	}
	reverse(rez.begin(), rez.end());
	return rez;
}

int64 toInt(string x) {
	int64 rez = 0;
	for (int i = 0; i < int(x.size()); i += 1) {
		rez *= 2;
		rez += x[i] - '0';
	}
	return rez;
}

int64 full[60];

int64 untilNow(int64 x) {
	int64 rez = 0;
	int len = 1;
	while ((1LL << len) - 1 < x) {
		rez += full[len];
		len += 1;
	}
	rez += 1LL * len * (x - (1LL << (len - 1)) + 1);
	return rez;
}

int main() {
	// string pattern = "";
	// for (int i = 1; i <= 100; i += 1) {
			// pattern += toString(i);
	// } fout << pattern << '\n';

	string txt; fin >> txt;

	for (int len = 1; len <= 55; len += 1) {
		full[len] = len * (1LL << (len - 1));
	}

	if (txt.find("1") == txt.npos) {
		fout << untilNow(1LL << (int(txt.size())));
		return 0;
	}

	// for (int i = 1; i <= 100; i += 1) {
		// fout << i << '\t' << untilNow(i) << '\n';
	// }

	int64 best = 1LL * inf * inf;

	for (int startPoz = 0; startPoz < int(txt.size()); startPoz += 1) {
		if (txt[startPoz] == '0') {
			continue;
		}

		for (int len = 1; len <= int(txt.size()); len += 1) {
			string currentNumber = txt.substr(startPoz, len);
			
			if (int(currentNumber.size()) != len) {
				// fout << "NOW\n";
				string before = txt.substr(0, startPoz);
				before = toString((toInt(before) + 1));
				reverse(before.begin(), before.end());
				while(len - int(currentNumber.size()) > int(before.size())) {
					before = "0" + before;
				}
				for (int i = len - int(currentNumber.size()) - 1; i >= 0; i -= 1) {
					currentNumber.push_back(before[i]);
				}
			}

			// fout << startPoz << '\t' << len << '\t' << currentNumber << '\n';

			int64 number = toInt(currentNumber);
			string rez = currentNumber;
			int64 nextNumber = number + 1;
			while (startPoz + int(rez.size()) <= int(txt.size())) {
				rez += toString(nextNumber);
				nextNumber += 1;
			}
			rez = rez.substr(0, int(txt.size()) - startPoz);

			int64 lastNumber = number - 1;
			while (int(rez.size()) < int(txt.size())) {
				rez = toString(lastNumber) + rez;
				lastNumber -= 1;
			}

			rez = rez.substr(int(rez.size()) - int(txt.size()), int(txt.size()));

			if (rez == txt) {
				best = min(best, untilNow(number - 1) + (int64)(txt.size()) - startPoz);
			}
		}
	}

	fout << best << '\n';
	return 0;
}