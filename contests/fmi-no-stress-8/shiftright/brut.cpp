#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int print = 0;
void Rotate(string& s, vector<int> ord) {
    if (ord.size() == 0) { return; }
    ord.push_back(ord[0]);
    char last_ch = s[ord[0]];
    for (int i = 1; i < (int)ord.size(); i += 1) {
        char c_char = s[ord[i]];
        s[ord[i]] = last_ch;
        last_ch = c_char;
    }
}

void Back(string given, string required, int moves_left) {
    if (given == required) {
        cout << print << '\n';
        exit(0);
    }

    if (moves_left == 0) {
        return;
    }


}

map<string, int> min_path;
map<string, string> parent;
queue<string> q;

void Expand(string given) {
    for (int i = 0; i < (1 << given.size()); i += 1) {
        vector<int> perm = {};
        for (int j = 0; j < (int)given.size(); j += 1) {
            if (i & (1 << j)) {
                perm.push_back(j);
            }
        }

        auto new_given = given;
        Rotate(new_given, perm);
        if (min_path.count(new_given) == 0) {
            parent[new_given] = given;
            min_path[new_given] = min_path[given] + 1;
            q.push(new_given);
        }
    }   
}

int main() {
    string given, required; cin >> given >> required;

    min_path[given] = 0;
    q.push(given);
    while (q.size() and min_path.count(required) == 0) {
        auto t = q.front();
        q.pop();
        Expand(t);
    }

    cout << min_path[required] << '\n';

     auto q = required;
    while (q != given) {
        cout << parent[q] << '\n';
        q = parent[q];
    }   
}
