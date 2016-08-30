#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream fin("revsecv.in");
ofstream fout("revsecv.out");

int main() {
	string txt; fin >> txt;

	int64 rez = 0;

	for (int mid = 0; mid < int(txt.size()); mid += 1) {
		// fixed mid
		int left = mid - 1, right = mid + 1;
		int current = 0;
		while (left >= 0 and right < int(txt.size())) {
			if (txt[left] == txt[right]) {
				current += 1;
			} else {
				current = 0;
			}

			rez += current;

			left -= 1;
			right += 1;
		}
	}

	for (int mid = 0; mid < int(txt.size()); mid += 1) {
		int left = mid, right = mid + 1;
		int current = 0;
		while (left >= 0 and right < int(txt.size())) {
			if (txt[left] == txt[right]) {
				current += 1;
			} else {
				current = 0;
			}

			rez += current;

			left -= 1;
			right += 1;
		}
	}

	fout << rez << '\n';
	return 0;
}