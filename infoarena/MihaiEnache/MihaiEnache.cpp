#include <cmath>
#include <iostream>
using namespace std;

const int MAX_FIB = 50;
long long fib[MAX_FIB];

int main() {
    fib[1] = 1;
	cerr << MAX_FIB << '\n';
    for (int i = 2; i <= MAX_FIB; i += 1) {
        fib[i] = fib[i - 2] + fib[i - 1];
        cerr << i << ' ' << fib[i] << endl;
    }
    cerr << "DONE" << endl;
    
    int T;
    cin >> T;
    for (int t = 1, N; t <= T; t += 1) {
        cin >> N;
        int step, pos;
        for (pos = 0, step = (1 << 5); step; step >>= 1)
            if (fib[pos + step] <= N) pos += step;
        
        if (fib[pos] == N)
            cout << "IsFibo\n";
        else
            cout << "IsNotFibo\n";
    }
}
