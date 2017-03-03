#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

typedef long long int64;

int Mod;
unordered_map<int, int> valid;

bool exists(int number) {
    return valid.find(number) != valid.end();
}

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5;

int& mod(int& a) {
    if (a >= Mod) {
        return a -= Mod;
    } else if (a < 0) {
        return a += Mod;
    } else {
        return a;
    }
}

int Pow(int a, int p) {
    int r = 1;
    while (p) {
        if (p & 1) {
            r = (1LL * r * a) % Mod;
        }
        a = (1LL * a * a) % Mod;
        p /= 2;
    }
    return r;
}

void Fail() {
    cout << "-1\n";
    exit(0);
}

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    time_t t = clock();
    int n; cin >> Mod >> n;
    vector<int> elements(n);
    for (auto& itr : elements) {
        cin >> itr;
    }

    for (auto itr : elements) {
        valid[itr] = true;
    }

    sort(elements.begin(), elements.end());

    if (n == 1) {
        cout << elements[0] << ' ' << 1 << '\n';
        exit(0);
    }

    vector<int> difs;
    for (int i = 1; i < n; i +=1 ) {
        difs.push_back(i);
    }
    random_shuffle(difs.begin(), difs.end());

    for (auto diff : difs) {    
        if ((1.0 * (clock() - t) / CLOCKS_PER_SEC) > 1.8) { Fail(); }
        int c = elements[0] - elements[1];
        mod(c);

        int r = (1LL * Pow(diff, Mod - 2) * c) % Mod;
        int num_right = 0;
        int num_left = 0;

        // search right;
        int val = elements[0];
        mod(val += r);
        while (exists(val) and num_left + num_right < n - 1) {
            num_right += 1;
            mod(val += r);
        }

        val = elements[0];
        mod(val -= r);
        while (exists(val) and num_left + num_right < n - 1) {
            num_left += 1;
            mod(val -= r);
        }       

        if (num_left + num_right == n - 1) {
            int start = (elements[0] - 1LL * r * num_left + 1LL * n * Mod) % Mod;
            cout << start << ' ' << r << '\n';
            exit(0);
        }
    }
    
    for (auto diff : difs) {    
        if ((1.0 * (clock() - t) / CLOCKS_PER_SEC) > 1.8) { Fail(); }
        int c = elements[1] - elements[0];
        mod(c);

        int r = (1LL * Pow(diff, Mod - 2) * c) % Mod;
        int num_right = 0;
        int num_left = 0;

        // search right;
        int val = elements[1];
        mod(val += r);
        while (exists(val) and num_left + num_right < n - 1) {
            num_right += 1;
            mod(val += r);
        }

        val = elements[1];
        mod(val -= r);
        while (exists(val) and num_left + num_right < n - 1) {
            num_left += 1;
            mod(val -= r);
        }       

        if (num_left + num_right == n - 1) {
            int start = (elements[1] - 1LL * r * num_left + 1LL * n * Mod) % Mod;
            cout << start << ' ' << r << '\n';
            exit(0);
        }
    }

    cout << "-1\n";
    return 0;
}
