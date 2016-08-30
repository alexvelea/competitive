#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 1e5+5;

vector<int> under[kMaxN], colors[kMaxN];

int color[kMaxN], result[kMaxN];

void df(int nod) {
    if (colors[color[nod]].size() == 0) {
        result[nod] = -1;
    } else {
        result[nod] = colors[color[nod]].back();
    }
   
    colors[color[nod]].push_back(nod);

    for (auto itr : under[nod]) {
        df(itr);
    }

    colors[color[nod]].pop_back();
}

int main() {
    int n, c; cin >> n >> c;
    for (int i = 2; i <= n; i += 1) {
        int p; cin >> p;
        under[p].push_back(i);
    }
    for (int i = 1; i <= n; i += 1) {
        cin >> color[i];
    }

    df(1);
    
    for (int i =1 ; i <= n; i +=1 ) {
        cout << result[i] << ' ';
    }
    return 0;
}
