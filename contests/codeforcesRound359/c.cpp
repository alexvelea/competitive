#include <iostream>
using namespace std;

int N, M;
int a = 0, b = 0;

int elements[7];
int visited[7];

int result = 0;

void bt(int n) {
    if (n == a + b) {
        int x = 0, y = 0;
        for (int i = 0; i < a; i += 1) {
            x *= 7;
            x += elements[i];
        }

        for (int j = a; j < a + b; j += 1) {
            y *= 7;
            y += elements[j];
        }

        if (x < N and y < M) {
            result += 1;
        }
    } else {
        for (int i = 0; i < 7; i += 1) {
            if (not visited[i]) {
                visited[i] = true;
                elements[n] = i;
                bt(n+1);
                visited[i] = false;
            }
        }
    }
}

int main() {
    cin >> N >> M;

    auto split = [](int x) {
        int result = 0;
        do {
            result += 1;
            x /= 7;
        } while (x);
        return result;
    };

    a = split(N-1);
    b = split(M-1);

    if (a + b > 7) {
        cout << 0 << '\n';
    } else {
        bt(0);
        cout << result << '\n';
    }
    return 0;
}

