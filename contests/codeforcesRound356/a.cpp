#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

int main() {
    vector<int> primes({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47});
    vector<int> found;

    for (auto itr : primes) {
        cout << itr << endl;
        string response; cin >> response;
        if (response == "yes") {
            found.push_back(itr);
        }
    }

    if (found.size() == 0) {
        cout << "prime" << endl;
    } else if (found.size() == 1) {
        int x = found[0] * found[0];
        if (x > 100) {
            cout << "prime" << endl;
            return 0;
        }
        cout << x << '\n';
        string response; cin >> response;
        if (response == "no") {
            cout << "prime" << endl;
        } else {
            cout << "composite" << endl;
        }
    } else if (found.size() > 1) {
        cout << "composite" << endl;
    }
    return 0;
}
