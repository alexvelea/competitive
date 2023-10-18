#include <iostream>
#include <vector>
#include <map>

using namespace std;

char winner(char a, char b) {
    if (a == b) {
        return a;
    }

    if (a == 'S') {
        if (b == 'P') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'P') {
        if (b == 'R') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'R') {
        if (b == 'S') {
            return a;
        } else {
            return b;
        }
    }

    return '!';
}

int main() {
    string s;
    int i = 0;
    while (cin >> s) {
//        cerr << "!" << s[s.size() - 1] << "!\n";
//        if (s[s.size() - 1] < 'A') {
//            s = s.substr(0, s.size() - 1);
//        }
//        cerr << s.size() << '\n';

        string s2 = "";
        while (s.size() > 1) {
            for (int j = 0; j < (int)s.size(); j += 2) {
                s2 += winner(s[j + 0], s[j + 1]);
            }
//            cerr << s << '\t' << s2 << '\n';
            s = s2;
            s2 = "";
        }
        i += 1;
        if (s[0] != 'S') {
            cerr << "!!\n";
        }
//        cout << i << '\t' << s[0] << '\n';
    }
}