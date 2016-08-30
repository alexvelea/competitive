#include <cassert>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

int result[1000];

// n >= 4
int64 F(int n) {
    if (n <= 3) {
        return 0;
    } else {
        return 1LL * n * n * (n + 1) * (n + 1) / 4 - 36;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int64 k; cin >> k;
    result[0] = 0;
    for (int i = 1; i < 216; i += 1) {
        int x = 1;
        while (x * x * x <= i) {
            x += 1;
        }
        x -= 1;
        result[i] = result[i - x * x * x] + 1;
    }
    
    int mx_num = 0;
    int64 mx_k = -1;

    for (int start = 0; start < 216; start += 1) {
        
        if (start > k) {
            continue;
        }

        int64 sum = start;
        int max_element = 6;
        int num = result[start];
        int inside = 0;

        while (1LL * max_element * max_element * max_element + sum <= k) {
            inside += 1;
            num += 1;
            sum += 1LL * max_element * max_element * max_element;
            max_element += 1;
        }

        if (inside != 0) {
            int64 current_sum = start;
            while (F(max_element) - F(max_element - inside) + current_sum <= k) {
                max_element += 1;
            }
            max_element -= 1;
            current_sum += F(max_element) - F(max_element - inside);
            sum = current_sum;
        }

        if (num > mx_num) {
            mx_num = num;
            mx_k = -1;
        }

        if (num == mx_num and sum > mx_k) {
            mx_k = sum;
        }
    }
    cout << mx_num << '\t' << mx_k << '\n';
    return 0;
}
