#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> words;
int ans = 0;

struct TrieNode {
    bool is_root = false;
    int down = 0;
    TrieNode* children[26];

    int Solve() {
        for (auto itr : children) {
            if (itr) {
                itr->Solve();
                down += itr->down;
            }
        }

        if (down >= 2 and is_root == false) {
            down -= 2;
            ans += 2;
        }
    }

    ~TrieNode() {
        for (auto& itr : children) {
            delete itr;
        }
    }
};

TrieNode *root;

void Insert(int word_id) {
    TrieNode *current = root;
    for (int i = 0; i < (int)words[word_id].size(); i += 1) {
        int c = words[word_id][i] - 'A';
        if (current->children[c] == nullptr) {
            current->children[c] = new TrieNode();
        }

        current = current->children[c];
    }

    current->down += 1;
}

int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {
        root = new TrieNode();
        root->is_root = true;

        int n; cin >> n;
        words.resize(n);
        for (auto& itr : words) {
            cin >> itr;
            reverse(itr.begin(), itr.end());
        }

        for (int i = 0; i < n; i += 1) {
            Insert(i);
        }

        root->Solve();

        cout << "Case #" << T << ": " << ans << '\n';

        words.clear();
        ans = 0;
        delete root;
    }
    return 0;
}
