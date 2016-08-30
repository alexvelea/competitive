#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef __int128_t  int128;
typedef long long   int64;

// LLLR
// RRL

string Solve(int128 a, int128 b, int128 n) {
    a -= 1;
    b -= 1;

    int128 num_bits=0;
    int128 start = a;
    int128 result = 0;
    int128 num_elements = 1;

    while (1) {
        int128 start_mod = start % (2 * n);
        int128 el_mod = b % (2 * n);
        int128 dist = 0;

        if (el_mod >= start_mod) {
            dist = el_mod - start_mod;
        } else {
            dist = el_mod - start_mod + n * 2;
        }

        if (dist < num_elements) {
            result = start + dist;
            break;
        } else {
            num_bits += 1;
            start *= 2;
            num_elements *= 2;
        }
    }           

    vector<int> bits;
    for (int i = 0; i < num_bits; i += 1) {
        bits.push_back(result % 2);
        result /= 2;
    }

    reverse(bits.begin(), bits.end());

//    cerr << num_bits << '\n';
//    cerr << a << "||\n";
//    for (auto itr : bits) {
//        cerr << itr << "|\n";
//    }

    {
    string result = "";
    int128 number = a;
    for (auto itr : bits) {
        if (number < n) {
            if (itr == 0) {
                result += "R"; 
            } else {
                result += "L";
            }
        } else {
            if (itr == 0) {
                result += "L";
            } else {
                result += "R";
            }
        }

        number *= 2;
        number += itr;
        number %= (2 * n);
    }

    return result;
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        int64 n, x, k; cin >> n >> x >> k;
        vector<int64> elements(k + 1);
        elements[0] = x;
        for (int i = 1; i <= k; i += 1) {
            cin >> elements[i];
        }
        cerr << k << '\n';

        string result;
        for (int i = 0; i < k; i += 1) {
            result += Solve(elements[i], elements[i + 1], n);
        }
        
        cout << result.size() << ":" << result << '\n';
    }
}
