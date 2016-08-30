#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1e5+5, kMod =1e9+9;

int pow(int a, int p) {
    int result = 1;
    while (p) {
        if (p & 1) {
            result = 1LL * result * a % kMod;
        }
        a = 1LL * a * a % kMod;
        p /= 2;
    }
    return result;
}

int main() {
    int t; cin >> t;

    vector<int> fact(kMaxN, 0);
    fact[0] = fact[1] = 1;
    for (int i = 2; i < kMaxN; i += 1) {
        fact[i] = 1LL * fact[i - 1] * i % kMod;
    }

    vector<int> invFact(kMaxN, 0);
    invFact[kMaxN - 1] = pow(fact[kMaxN - 1], kMod - 2);
    invFact[0] = 1;
    invFact[1] = 1;
    for (int i = kMaxN - 2; i; i -= 1) {
        invFact[i] = 1LL * invFact[i + 1] * (i + 1) % kMod;
    }

    for (int i = 0; i < t; i += 1) {
        int n; cin >> n;
        vector<int> elements(n + 1, 0); 
        for (int i = 1; i <= n; i += 1) {
            cin >> elements[i];
        }

        vector<int> sizes;
        vector<bool> visited(n + 1, false);
        for (int i = 1; i <= n; i += 1) {
            if (visited[i]) {
                continue;
            }

            int current_size = 0;
            int nod = i;
            while (not visited[nod]) {
                visited[nod] = true;
                current_size += 1;
                nod = elements[nod];
            }

            sizes.push_back(current_size);
        }

        int min_num = 0;
        int erase = 1;
        for (auto itr : sizes) {
            if (itr > 1) {
                min_num += itr - 1;
                erase = 1LL * erase * invFact[itr - 1] % kMod;
            }
        }
    
        int result = 1LL * fact[min_num] * erase % kMod;
        for (auto itr : sizes) {
            if (itr > 2) {
                result = 1LL * result * pow(itr, itr - 2) % kMod;
            }
        }

        cout << result << '\n';
/*
        for (auto itr : elements) {
            cout << itr << '\t';
        }
        cout << '\n';
*/
    }
    return 0;
}
