#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;
 
ifstream fin("sume.in");
ofstream fout("sume.out");
 
const int MAX_P = 25100;
const int MAX_N = 200;
const int MAX_NUM = 5001;
 
int P;
int N;
int initial[MAX_N];
int ap[MAX_NUM];
int cut_sums[MAX_P];
 
int main() {
    fin >> P;
	assert (P < MAX_P);
    for (int i = 1, x; i <= P; ++i) {
        fin >> x;
		assert (x >= 0);
		assert (x <= 1000);
		ap[x]++;
    }
 
    N = int(sqrt(2 * P)) + 1;
    bool found_solution = false;
    int contor = 0;
	int a = MAX_NUM-1;
 	while (!ap[a])
		--a;
    for (int i = a/2; i <= a && !found_solution; ++i) {
		for (int j = 1; j <= contor; ++j) {
			ap[cut_sums[j]] ++;
		}
		contor = 0;
        found_solution = true;
        initial[1] = i;
		int mx = MAX_NUM-1;
        for (int j = 2; j <= N && found_solution; ++j) {
			while (!ap[mx])
				--mx;
            initial[j] = mx - i;
			if (initial[j] > initial[j-1]) {
				found_solution = false;
				break;
			}

			for (int k = 1; k < j; ++k) {
                if (initial[j] + initial[k] < 0)
					assert(0);
                if (initial[j] + initial[k] < 0 || ap[initial[j] + initial[k]] == 0) {
					found_solution = false;
                    break;
				} else {
					ap[initial[j] + initial[k]]--;
                    cut_sums[++contor] = initial[j] + initial[k];
                }
            }
        }
    }
 
    if (found_solution) {
        fout << N << '\n';
        for (int i = 1; i <= N; ++i) {
            fout << initial[i] << ' ';
        }
    } else {
        fout << -1;
    }
 
    return 0;
}
