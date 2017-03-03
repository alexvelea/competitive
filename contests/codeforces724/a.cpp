#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> days = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    string a, b; cin >> a >> b;
    int A = 0, B = 0;
    for (int i = 0; i < 7; i += 1) {
        if (days[i] == a) {
            A = i;
        }
        if (days[i] == b) {
            B = i;
        }
    }

    vector<int> mon = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 0; i < 11; i += 1) {
        if ((A + mon[i]) % 7 == B) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
