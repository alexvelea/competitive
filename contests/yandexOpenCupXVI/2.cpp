//Problem 2 @ 04-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

#define int64 long long

pair<int, int> win[(1 << 19) - 5];
unordered_map<string, int> where;

string team[(1 << 19) - 5];
int winner[(1 << 19) - 5];

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < (1 << n); ++i) {
        cin >> team[i];
        win[i] = {i, i};
        where[team[i]] = i;
    }
    
    int game = 0;
    int otherStart = 0;
    for (int i = 0; i < (1 << (n)); i += 2) {
        char c; cin >> c;
        if (c == 'W') {
            winner[game] = i;
        } else {
            winner[game] = i + 1;
        }
        win[winner[game]] = {i, i + 1};
        ++game;
    }

    for (int i = 2; i <= n; ++i) {
        int start = game;
        for (int j = 0; j < 1 << (n - i); ++j) {
            char c; cin >> c;
            if (c == 'W') {
                winner[game] = winner[otherStart + 2 * (game - start)];
            } else {
                winner[game] = winner[otherStart + 2 * (game - start) + 1];
            }
            win[winner[game]] = 
            make_pair(
                win[winner[otherStart + 2 * (game - start)]].first, 
                win[winner[otherStart + 2 * (game - start) + 1]].second
            );
 
            ++game;
        }
        otherStart = start;
    }
//    for (int i = 0; i < (1 << n); ++i) {
//        cout << i << '\t' << team[i] << '\t' << win[i].first << '\t' << win[i].second << '\n';
//    }

    int q; cin >> q;
    while (q--) {
        string a, b;
        cin >> a >> b;
        int pozA = where[a];
        int pozB = where[b];
        pair<int, int> winA = win[pozA], winB = win[pozB];

        if (winA.first <= pozB and pozB <= winA.second) {
            cout << "Win\n";
        } else if (winB.first <= pozA and pozA <= winB.second) {
            cout << "Lose\n";
        } else {
            cout << "Unknown\n";
        }
    }    
	return 0;
}
