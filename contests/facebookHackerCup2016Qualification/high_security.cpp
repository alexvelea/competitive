#include <fstream>
#include <iostream>
#include <string>
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
		int n; cin >> n;
		int answer = 0;

		string matrix[2];
		vector<int> length[2];

		cin >> matrix[0] >> matrix[1];

		for (int row = 0; row < 2; row += 1) {
			for (int col = 0; col < n; col += 1) {
				if (matrix[row][col] == 'X') {
					length[row].push_back(0);
					continue;
				}

				int back = 0;

				if (col != 0) {
					back = length[row].back();
				}

				length[row].push_back(back + 1); 
			}
		}

		for (int row = 0; row < 2; row += 1) {
			for (int col = n - 2; col >= 0; col -= 1) {
				if (matrix[row][col] == 'X') {
					continue;
				}
				length[row][col] = max(length[row][col], length[row][col + 1]);
			}
		}

		for (int row = 0; row < 2; row += 1) {
			for (int col = 0; col < n; col += 1) {
				if (length[row][col] == 0) {
					continue;
				}

				answer += 1;
				col += length[row][col] - 1;
			}
		}

		for (int row = 0; row < 2; row += 1) {
			for (int col = 0; col < n; col += 1) {
				if (length[row][col] == 0) {
					continue;
				}

				int target_col = col + length[row][col] - 1;
				while (col <= target_col) {
					if (length[row ^ 1][col] == 1) {
						answer -= 1;
						length[row ^ 1][col] = 0;
						break;
					}

					col += 1;
				}

				col = target_col;
			}
		}

		cout << "Case #" << test << ": " << answer << '\n';
	}	
	return 0;
	return 0;
}