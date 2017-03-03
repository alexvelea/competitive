#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    string s; cin >> s;
    int n = s.size();
    char last = '?';
    vector<int> answer;
    for (int i = 0; i < n; i += 3) {
        string c = "";
        c += s[i];
        c += s[i + 1];
        c += s[i + 2];
        char next_l = c[2];

        if (c == "001") {
            answer.push_back(i + 1);
            next_l = '0';
        }

        if (c == "110") {
            answer.push_back(i + 1);
            next_l = '1';
        }

        if (c == "010" or c == "101") {
        }
        
        if (c == "011" or c == "100") {
            answer.push_back(i);
        }
        

        if (c == "000") {
            if (last == '?') {
                answer.push_back(i);
            } else if (last == '1') {
                answer.push_back(i + 1);
                next_l = '1';
            } else if (last == '0') {
                answer.push_back(i);
            }
        } else if (c == "111") {
            if (last == '?') {
                answer.push_back(i);
            } else if (last == '0') {
                answer.push_back(i + 1);
                next_l = '0';
            } else if (last == '1') {
                answer.push_back(i);
           }
        }

        last = next_l;
    }

    cout << answer.size() << '\n';
    for (auto itr : answer) {
        cout << itr + 1 << ' ';
    }
    cout << '\n';
    for (auto itr : answer) {
        s[itr] ^= 1;
        s[itr + 1] ^= 1;
    }
    int sum = 0;
    for (int i = 0; i + 1 < n; i += 1) {
        sum += s[i] != s[i + 1];
    }
    assert(sum + 1 >= (n / 3) * 2);
    return 0;
}
