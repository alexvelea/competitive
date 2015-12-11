#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

#define int64 long long

const int kMaxVal = 5e5 + 5;

ifstream fin("porcjoc.in");
ofstream fout("porcjoc.out");

unordered_map<int, int> how_many;
vector<pair<int, int> > elements;

int divisor[kMaxVal];

int64 here[kMaxVal];

int main() {
    int n; fin >> n;
    for (int i = 0; i < n; i += 1) {
        int a, b; fin >> a >> b;
        how_many[a] += b;
    }

    for (auto itr : how_many) {
        elements.push_back(itr);
    }

    for (int i = 2; i * i < kMaxVal; i += 1) {
        if (divisor[i] != 0) {
            continue;
        }

        for (int j = i * i; j < kMaxVal; j += i) {
            if (divisor[j] == 0) {
                divisor[j] = i;
            }
        }
    }

    for (int i = 2; i < kMaxVal; i += 1) {
        if (divisor[i] == 0) {
            divisor[i] = i;
        }
    }

    auto desc = [](int x) {
        vector<int> primes;
        int last_prime = -1;
        while (x > 1) {
            if (divisor[x] != last_prime) {
                last_prime = divisor[x];
                primes.push_back(divisor[x]);
            }
            x = x / divisor[x];
        }
        vector<pair<int, int> > result_vector;
        for (int s = 0; s < (1 << int(primes.size())); s += 1) {
            int rez = 1, nr = 0;
            for (int i = 0; i < int(primes.size()); i += 1) {
                if (s & (1 << i)) {
                    nr ^= 1;
                    rez *= primes[i];
                }
            }
            result_vector.push_back({rez, nr});
        }
        return result_vector;
    };

    for (auto itr : elements) {
        auto x = desc(itr.first);
        int op[2] = {+1, -1};
        for (auto y : x) {
            here[y.first] += op[y.second] * itr.second;
        }
    }

    int64 a = 0;

    for (auto itr : elements) {
        int64 now = 0;
        auto x = desc(itr.first);
        for (auto y : x) {
            now += here[y.first];
        }
        a += now * itr.second;
    }                        

    int64 b = 0;
    for (auto itr : elements) {
        b += itr.second;
    }
    b *= b;
    int64 d = __gcd(a, b);

    fout << a/d << '/' << b/d << '\n';
    
    return 0;
}
