#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

vector<int> values;

int num_calls = 0;

map<pair<int, vector<int>>, int> number;

int Get(int sum, vector<int> bad_elements) {
    if (number.find(make_pair(sum, bad_elements)) != number.end()) {
        return number[make_pair(sum, bad_elements)];
    }
/*
    cerr << sum << '\t';
    for (auto itr : bad_elements) {
        cerr << itr << '\t';
    }
        cerr << ++num_calls << '\n';
*/

    vector<int> bad(61, 0);
    for (auto itr : bad_elements) {
        bad[itr] = true;
    }

    vector<int> v;
    if (sum == 0) {
        return 0;
    }

    for (int i = 1; i <= sum; i += 1) {
        if (bad[i]) {
            continue;
        }

        bad_elements.push_back(i);
        sort(bad_elements.begin(), bad_elements.end());
 
        v.push_back(Get(sum - i, bad_elements));

        for (int j = 0; j < (int)bad_elements.size(); j += 1) {    
            if (bad_elements[j] == i) {
                swap(bad_elements[j], bad_elements.back());
                bad_elements.pop_back();
                break;
            }
        }   
    }

    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    
    int ans = v.size();
    for (int i = 0; i < (int)v.size(); i += 1) {
        if (i != v[i]) {
            ans = i;
            break;
        }
    }
    
    sort(bad_elements.begin(), bad_elements.end());
    number[make_pair(sum, bad_elements)] = ans;
    return ans;
}

void Gen(int first_element, int sum) {
    
    if (first_element + sum > 60) {
        return;
    }

    values.push_back(first_element);
    Gen(first_element + 1, sum + first_element);
    values.pop_back();
    Gen(first_element + 1, sum);
}

int mex[61] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10};

int main() {
    ios_base::sync_with_stdio(false);
    Gen(0, 0);
    for (int i = 1; i <= 60; i += 1) {
//        cout << Get(i, {}) << ", ";
    }

    int sum = 0;
    int n; cin >> n;
    for (int i = 0; i < n; i += 1) {
        int itr; cin >> itr;
        sum ^= mex[itr];
    }

    if (sum) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
    return 0;
}
