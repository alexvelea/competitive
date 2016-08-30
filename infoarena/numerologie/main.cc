#include <cassert>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream fin("numerologie.in");
ofstream fout("numerologie.out");

const int inf = 0x3f3f3f3f;
const int kMaxM = 1350;

vector<int> cost(kMaxM, inf);
bool selected[kMaxM];
int prime[kMaxM];

int main() {
    int n, m; fin >> n >> m;
    vector<int> numbers(n);
    for (int i = 0; i < n; i += 1) {
        fin >> numbers[i];
    }

    for (int i = 1; i <= m; i += 1) {
        fin >> cost[i];
    }

    for (int i = 2; i < kMaxM; i += 1) {
        if (prime[i] != 0) {
            continue;
        }
        
        for (int j = i; j < kMaxM; j += i) {
            prime[j] = i;
        }
    }

    int64 best_cost = 1LL * inf * inf;

    int first_primes[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (int s = 0; s < (1 << 11); s += 1) {
        for (int i = 0; i < kMaxM; i += 1) {
            selected[i] = 0;
        }

        for (int i = 0; i < 11; i += 1) {
            if (s & (1 << i)) {
                selected[first_primes[i]] = true;
            }
        }

        for (auto itr : numbers) {
            bool finded = false;
            int num = itr;
            while (not finded and num != 1) {
                if (selected[prime[num]]) {
                    finded = true;
                }
                
                assert(prime[num] != 0);
                num /= prime[num];
            }

            if (not finded) {
                selected[prime[itr]] = true;
            }
        }
        
        int64 current_cost = 0;
        for (int i = 0; i < kMaxM; i += 1) {
            if (selected[i]) {
                current_cost += cost[i];
            }
        }
        if (current_cost < best_cost) {
            best_cost = current_cost;
        }
    }

    fout << best_cost << '\n';
    return 0;
}
