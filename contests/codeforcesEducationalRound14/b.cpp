#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

map<char, vector<int>> mirror;

int main() {
    ios_base::sync_with_stdio(false);
    mirror['A'].push_back('A');
    mirror['H'].push_back('H');
    mirror['I'].push_back('I');
    mirror['M'].push_back('M');
    mirror['O'].push_back('O');
    mirror['T'].push_back('T');
    mirror['U'].push_back('U');
    mirror['V'].push_back('V');
    mirror['W'].push_back('W');
    mirror['X'].push_back('X');
    mirror['Y'].push_back('Y');
   
    mirror['o'].push_back('o');
    mirror['v'].push_back('v');
    mirror['w'].push_back('w');
    mirror['x'].push_back('x');

    mirror['b'].push_back('d');
    mirror['d'].push_back('b');
    
    mirror['p'].push_back('q');
    mirror['q'].push_back('p');

    string txt; cin >> txt;
    int n = (int)txt.size();
    bool k = true;
    for (int i = 0; i < n; i += 1) {
        int oth = (int)txt[n - i - 1];
        bool ok = false;
        for (auto itr : mirror[txt[i]]) {
            if (itr == oth) {
                ok = 1;
            }
        }
        k &= ok;
    }

    if (k) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }
    return 0;
}
