#include <iostream>
using namespace std;
int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {
        auto Print = [&](string a, string b) {
            cout << "Case #" << T << ": ";
            {
                int i = 0;
                for (; i < (int)a.size() and a[i] == '0'; i += 1) { }
                for (; i < (int)a.size(); i += 1) { cout << a[i]; } 
            }

            cout << ' ';
            
            {
                int i = 0;
                for (; i < (int)b.size() and b[i] == '0'; i += 1) { }
                for (; i < (int)b.size(); i += 1) { cout << b[i]; } 

            }           

            cout << '\n';
        };


        string x; cin >> x;
        string a = x, b = x;

        bool only_1 = true;

        for (auto& itr : x) { 
            if (itr != '1') {
                only_1 = false;
            }
        }

        if (only_1) {
            a[0] = '0';
            b = string(x.size(), '0');
            b[0] = '1';

            Print(a, b);
            continue;
        }

        for (int i = 0; i < (int)x.size(); i += 1) {
            for (int j = 0; j < 9; j += 1) {
                int oth = a[i] - '0' - j;
                if (0 <= oth and oth <= 9 and oth != 4 and j != 4) {
                    a[i] = '0' + oth;
                    b[i] = '0' + j;
                    break;
                }
            }
        }

        Print(a, b);

    }
    return 0;
}
