#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("cuvant.in");
ofstream out("cuvant.out");

const int kMaxN = 10005, Mod = 666013;

int fact[kMaxN], invFact[kMaxN];

int pow(int a, int p) {
    int rez = 1;
    while (p) {
        if (p & 1)
            rez = (1LL * rez * a) % Mod;
        a = (1LL * a * a) % Mod;
        p /= 2;
    }
    return rez;
}

string txt;
int ap[26];
int dp[1005];

int main() {
    fact[1] = invFact[1] = 1;
    for (int i = 2; i < kMaxN; ++i)
        fact[i] = (1LL * fact[i - 1] * i) % Mod;
    fact[0] = invFact[0] = 1;
    for (int i = 2; i < kMaxN; ++i)
        invFact[i] = pow(fact[i], Mod - 2);
    
    int t;
    in >> t;
    while (t--) {
        in >> txt;
        int l;
        in >> l;
        
        for (int i = 0; i < 26; ++i)
            ap[i] = 0;
        
        for (int i = 0; i < int(txt.size()); ++i)
            ap[txt[i] - 'a']++;
        
        for (int i = 0; i < 26; ++i)
			ap[i] = 1000;
		l = 1000;

        for (int i = 1; i <= 1000; ++i)
            dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < 26; ++i) {
            for (int x = l; x >= 0; --x) {
                for (int y = 1; y <= (l - x) and y <= ap[i]; ++y) {
                    dp[x + y] += (1LL * dp[x] * (1LL * ((1LL * fact[l - x] *  invFact[l - x - y]) % Mod) * invFact[y]) % Mod) % Mod;
					if (dp[x + y] >= Mod)
						dp[x + y] -= Mod;
                }
            }
        }
        out << dp[l] << '\n';
    }
    return 0;
}
