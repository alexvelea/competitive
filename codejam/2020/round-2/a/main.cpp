#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef long long int64;

struct Ans {
    int64 num = 0;
    int64 l = 0, r = 0;
};

int64 NumForDif(int64 dif) {
    int64 num = 0;
    for (int p = 31; p >= 0; p -= 1) {
        int64 now = num + (1LL << p);
        if (now * (now + 1) / 2 <= dif) {
            num = now;
        }
    }

    return num;
};

Ans Solve(int64 a, int64 b) {
    Ans ans;
    int64 dif = abs(a - b);
    int64 t = NumForDif(dif);
    ans.num += t;
    if (a > b) {
        a -= t * (t + 1) / 2;
    } else {
        b -= t * (t + 1) / 2;
    }

//    cerr << "Initial served " << t << " remaining: " << a << ' ' << b << '\n'; 


    bool swapped = false;
    if (b > a) {
        swap(a, b);
        swapped = true;
    }

    // One from each
    // The order is (small num to the larger, big num to the small one)
    // each iteration diff increase by 1
    int64 each = 0;
    for (int p = 31; p >= 0; p -= 1) {
        int64 now = each + (1LL << p);
        int64 a_sum = t * now + now * now;
        int64 b_sum = t * now + now * (now + 1);
        if (a_sum <= a and b_sum <= b) {
//            cerr << "Ok\t" << a_sum << '\t' << b_sum << '\n';
            each = now;
        }
    }

//    cerr << "Each: " << each << '\n';
//    cerr << "Ans.num = " << ans.num << '\n';
    ans.num += 2 * each;
    a -= t * each + each * each;
    b -= t * each + each * (each + 1);
    t += 2 * each;

    if (a >= t + 1) {
        a -= t + 1;
        ans.num += 1;
        ans.l += 1;
        t += 1;
    }

    if (a >= t + 1) {
        assert(false);
    }
    if (b >= t + 1) {
        assert(false);
    }

    if (swapped) {
        swap(a, b);
    }

    ans.l = a;
    ans.r = b;

    return ans;
}

int main() {
    int T; cin >> T;

    for (int t = 1; t <= T; t += 1) {
        int64 a, b; cin >> a >> b;
        
        auto ans = Solve(a, b);
        

        cout << "Case #" << t << ": ";
        cout << ans.num << ' ' << ans.l << ' ' << ans.r << '\n';
    }

    return 0;
}
