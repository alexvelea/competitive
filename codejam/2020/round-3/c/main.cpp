#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 15;

double max_expected[1 << kMaxN];
bool should_stop[1 << kMaxN];

double FindChx(const vector<int>& available_nums) {
    int ok = 0;
    int total = 0;
    for (int i = 0; i < (int)available_nums.size(); i += 1) {
        for (int j = i + 1; j < (int)available_nums.size(); j += 1) {
            total += 1;
            if (available_nums[i] + available_nums[j] >= kMaxN) {
                ok += 1;
            }
        }
    }

    return 1.0 * ok / total;
}

void PrintBinary(int x) {
    for (int i = 0; i < kMaxN; i += 1) {
        cerr << !!((1 << i) & x);
    }
}

void Init() {
    for (int i = (1 << kMaxN) - 1; i >= 0; i -= 1) {
        vector<int> available_nums;
        for (int j = 0; j < kMaxN; j += 1) {
            if (i & (1 << j)) { } else {
                available_nums.push_back(j);
            }
        }

        max_expected[i] = FindChx(available_nums);
        if (available_nums.size() <= 2) {
            should_stop[i] = true;
            continue;
        }

        double move_sum = 0;
        for (auto& itr : available_nums) {
            move_sum += max_expected[(1 << itr) | i];
        }

        move_sum /= available_nums.size();
        
//        PrintBinary(i); cerr << fixed << setprecision(4) << ' ' << move_sum << ' ' << max_expected[i] << '\n';

        if (max_expected[i] > move_sum) {
            should_stop[i] = true;
        } else {
            max_expected[i] = move_sum;
        }
    }
}

struct TestCase {
    vector<int> known_numbers;
    int current_num;
    int pos;
    bool running = true;
    void Apply(int x) {
        if (x == 0) {
            known_numbers.push_back(current_num);
            pos += 1;
            Rethink();
        } else {
            current_num += 1;               
        }
    }

    void Rethink() {
        int state = 0;
        for (auto& itr : known_numbers) {
            state |= (1 << itr);
        }

        running = should_stop[state];
    }
};

int main() {
    Init();
//    cerr << max_expected[0] << '\n';
//    cerr << should_stop[0] << '\n';

    int n, c, T;
    cin >> T >> n >> c;
    vector<TestCase> tests(T);
    while (1) {
        bool ok = false;
        for (int i = 0; i < T; i += 1) {
            if (tests[i].running) {
                ok = true;
            }
        }

        if (not ok) {
            break;
        }

        for (int i = 0; i < T; i += 1) {
            if (tests[i].running) {
                cout << tests[i].pos + 1 << ' ';
            } else {
                cout << 0 << ' ';
            }
        }
        cout << endl;

        for (int i = 0; i < T; i += 1) {
            int x; cin >> x;
            if (tests[i].running) {
                tests[i].Apply(x);
            }
        }
    }

    for (int i = 0; i < T; i += 1) {
        cout << 0 << ' ';
    } cout << endl;
    for (int i = 0; i < T; i += 1) {
        cout << tests[i].pos << ' ' << tests[i].pos + 1 << ' ';
    }
    cout.flush();
    return 0;
}
