#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

//ifstream fin("circus.in");
ifstream fin("test.07.in");
ofstream fout("circus.out");

const int kMaxN = 1e5 + 5, inf = 0x3f3f3f3f;

int el[kMaxN], best[kMaxN];

int main() {
    int n, m; fin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fin >> el[i];
        if (el[i] >= m) {
            --i;
            --n;
        }
    }
    el[++n] = m;

    for (int i = 1; i <= n; ++i) {
        best[i] = m - el[i];
    }
    
    sort(el + 1, el + n + 1);
    
    for (int i = 1; i <= n; ++i) {
        cerr << el[i] << '\n';
    }

    priority_queue<pair<int, int> > pq; // .second = 0 -> update, != 0 -> indicele elementului 
    for (int i = 1; i < n; ++i) {
        pq.push(make_pair(el[i], -i));
    }
    pq.push(make_pair(m, m));
    int closest = m;

    vector<pair<int, int> > event;
    event.reserve(2 * n);
    event.push_back(make_pair(m, m));
    while (pq.size()) {
        int d = pq.top().first;
        int upd = pq.top().second;
        pq.pop();
        if (upd >= 0) {
            if (closest > upd) {
                event.push_back(make_pair(d, upd));
                closest = upd;
            }
        } else {
            upd *= -1;
            best[upd] = closest - el[upd];
            pq.push(make_pair(el[upd] - best[upd], el[upd]));
        }
    }
    reverse(event.begin(), event.end());
    
     
    for (int i = 1; i <= n; ++i) {
        cerr << el[i] << '\t' << best[i] << '\n';
    } 
 

    int q; fin >> q;
    if (fin >> q) {
        pair<int, int> aux = {q, -inf};
        cerr << q << '\n';
        auto itr = lower_bound(event.begin(), event.end(), aux);
        fout << itr->second - q << '\n';
    }

    return 0;
}

