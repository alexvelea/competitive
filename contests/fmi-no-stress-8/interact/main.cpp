#include <iostream>
using namespace std;

bool Query(string s) {
    if (s.size() == 101) {
        return false;
    }
    cout << "? " << s << endl;
    bool k; cin >> k; return k;
}

int main() {
    string s = "";
    for (char c = 'a'; c <= 'z'; c += 1) {
        for (int pos = 0; pos <= (int)s.size(); pos += 1) {
            string q = s.substr(0, pos) + string(1, c) + s.substr(pos, s.size());
            if (Query(q)) {
                s = q;
            }
        }
    }

    cout << "! " << s << endl;
    int x; cin >> x;

    return 0;
}
