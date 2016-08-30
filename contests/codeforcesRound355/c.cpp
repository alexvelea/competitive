#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int mod = 1e9+7;;

map<char, int> size;

int main() {
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 10; i += 1) {
        size[char('0' + i)] = i;
    }
    for (int i = 0; i < 26; i += 1) {
        size[char('A' + i)] = i + 10;
    }
    for (int i = 0; i < 26; i += 1) {
        size[char('a' + i)] = i + 10 + 26;
    }   
    size['-'] = 62;
    size['_'] = 63;

    vector<int> result(64);
    for (int i = 0; i < 64; i += 1) {
        result[i] = 1;
        for (int j = 0; (1 << j) < 64; j += 1) {
            if ((i & (1 << j)) == 0) {
                result[i] = (1LL * result[i] * 3) % mod;
            }
        }
    }
    
    string txt; cin >> txt;
    int res = 1;
    for (char itr : txt) {
        res = (1LL * res * result[size[itr]]) % mod;
    }
    cout << res << '\n';
    return 0;
}
