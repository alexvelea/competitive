#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream fin("input.txt");
ofstream fout("output.txt");

#define cin fin
#define cout fout

int main() {
	int nr_of_testcases; cin >> nr_of_testcases;
	for (int test = 1; test <= nr_of_testcases; test += 1) {
		int n, p; cin >> n >> p;
		int64 answer = 0;

		int64 current_sum = 0;
		vector<int64> partial_sums = {0};
		for (int i = 1; i <= n; i += 1) {
			int x; cin >> x;
			current_sum += x;
			partial_sums.push_back(current_sum);
		}

		int st = 1;
		for (int dr = 1; dr <= n; dr += 1) {
			while (partial_sums[dr] - partial_sums[st - 1] > p) {
				st += 1;
			}

			answer += dr - st + 1;
		}

		cout << "Case #" << test << ": " << answer << '\n';
	}	
	return 0;
}
