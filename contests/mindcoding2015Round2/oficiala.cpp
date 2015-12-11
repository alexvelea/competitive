#include <bits/stdc++.h>

using namespace std;

const int buffer=1<<13;
char buff[buffer]; int cnt=0;

//getInt() reads and returns one integer at a time
int getInt() {
    int number = 0;
    while(buff[cnt] < '0' || '9' < buff[cnt])
        if(++cnt >= buffer) fread(buff, buffer, 1, stdin), cnt = 0;
    
    while('0' <= buff[cnt] && buff[cnt] <= '9') {
        number = number * 10 + buff[cnt] - '0';
        if(++cnt >= buffer) fread(buff, buffer, 1, stdin), cnt = 0;
    }
    
    return number;
}

#define MAXN 100050

int N, M;
int T[MAXN];
int sz[MAXN];
int st[MAXN][2];
int p;

int root(int n) {
    if (T[n] == n) {
        return n;
    }
    return root(T[n]);
}

pair<int, int> unite(int a, int b) {
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    T[b] = a;
    sz[a] += sz[b];
    return { a, b };
}

void disconnect(int a, int b) {
    T[b] = b;
    sz[a] -= sz[b];
}

int main() {
    //	freopen("date.in", "r", stdin);
    //	freopen("date.out","w", stdout);
    
    N = getInt();
    M = getInt();
    
    for (int i = 0; i < N; i++) {
        T[i] = i;
        sz[i] = 1;
    }
    
    p = 0;
    int t = -1;
    int x = -1;
    int y = -1;
    int rx = -1;
    int ry = -1;
    int same = -1;
    int a = -1;
    int b = -1;
    pair<int, int> op(-1, -1);
    for (int id = 0; id < M; id++) {
        t = getInt();
        if (t == 1) {
            x = getInt() - 1;
            y = getInt() - 1;
            rx = root(x);
            ry = root(y);
            op = { -1, -1 };
            if (rx != ry) {
                op = unite(rx, ry);
            }
            st[p][0] = op.first;
            st[p][1] = op.second;
            p++;
        }
        else if (t == 2) {
            x = getInt();
            while (x-- > 0) {
                p--;
                a = st[p][0];
                b = st[p][1];
                if (a != -1) {
                    disconnect(a, b);
                }
            }
        }
        else {
            x = getInt() - 1;
            y = getInt() - 1;
            rx = root(x);
            ry = root(y);
            same = (rx == ry);
            printf("%d\n", same);
        }
    }
    
    return 0;
}
