#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

typedef long long int64;

const int kMaxN = 1e3+5;

const int kBufferSize = 1e4;
int bufferInd = kBufferSize;
char buffer[kBufferSize];

void nextChar() {
    if (++bufferInd >= kBufferSize) {
        cin.read(buffer, kBufferSize);
        bufferInd = 0;
    }
}

bool valid(char c) {
    return (c == '-' or ('0' <= c and c <= '9'));
}

char currentChar() {
    if (bufferInd > kBufferSize) {
        nextChar();
    }
    return buffer[bufferInd];
}

template<typename number>
void readNumber(number &a) {
    a = 0;
    bool signedNumber = false;
    if (currentChar() == '-') {
        signedNumber = true;
    }

    for (; not valid(currentChar()); nextChar())
        ;

    for (; valid(currentChar()); nextChar()) {
        a *= 10;
        a += currentChar() - '0';
    }

    if (signedNumber) {
        a *= -1;
    }
    return ;
}

struct Edge {
    int a, b, c, i;
    bool operator<(const Edge& rhs) const {
        return c < rhs.c;
    }
};

vector<Edge> edges;
int n, m, q;

int group[kMaxN];
int father[2 * kMaxN];
int enemy[2 * kMaxN];

vector<int> inside[2 * kMaxN];

void join(int a, int b) {
    if (rand() % 2) {
        swap(a, b);
    }
    for (auto itr : inside[b]) {
        father[itr] = a;
    }
    inside[a].insert(inside[a].end(), inside[b].begin(), inside[b].end());
}

int GetFather(int a) {
    if (father[a] != a) {
        father[a] = GetFather(father[a]);
    }
    return father[a];
}

int Solve(int l, int r) {
    for (int i = 1; i <= 2 * n; i += 1) {
        father[i] = i;
        inside[i].clear();
        inside[i].push_back(i);
    }
    for (int i = 1; i <= n; i += 1) {
        enemy[i] = n + i;
        enemy[n + i] = i;
    }

    for (auto itr : edges) {
        if (itr.i >= l and itr.i <= r) {
            int pa = GetFather(itr.a);
            int pb = GetFather(itr.b);

            if (pa == GetFather(enemy[pb])) {
                continue;
            }

            if (pa == pb) {
                return itr.c;
            } else {
                int ea = GetFather(enemy[pa]);
                int eb = GetFather(enemy[pb]);

                join(eb, pa);
                join(ea, pb);
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    readNumber(n);
    readNumber(m);
    readNumber(q);
    edges.reserve(m);
    for (int i = 1; i <= m; i += 1) {
        int x, y, c; 
        readNumber(x);
        readNumber(y);
        readNumber(c);
        Edge e;
        e.a = x;
        e.b = y;
        e.c = c;
        e.i = i;
        edges.push_back(e);
    }

    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    
    for (int i = 0; i < q; i += 1) {
        int l, r;
        readNumber(l);
        readNumber(r);
        cout << Solve(l, r) << '\n';              
    }
    return 0;
}
