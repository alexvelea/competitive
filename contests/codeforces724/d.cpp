#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

vector<int> here[30];

int Result(const vector<int>& a, const vector<int>& b, int m) {
    int result = 0;
    int cb = 0;
    int last = a[0];
    for (int i = 1; i < (int)a.size(); i += 1) {
//        cerr << last << '\t' << a[i] << '\n';
        if (a[i] - last < m + 1) {
            last = a[i];
            continue;
        }

        while (cb + 1 < (int)b.size() and b[cb + 1] - last < m + 1) {
//            cerr << "Skip\t" << cb << '\n';
            cb += 1;
        }

        if (cb < (int)b.size() and b[cb] - last < m + 1) {
//            cerr << "Add\t" << cb << '\n';
            last = b[cb];
            cb += 1;
            i -= 1;
            result += 1;
            continue;
        } else {
            return -1;
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    int m; cin >> m;
    string txt; cin >> txt;
    int n = txt.size();
    for (int i = 0; i < n; i += 1) {
        here[(int)txt[i] - 'a'].push_back(i);
    }
    
    vector<int> intervals = {-1, n};
    string result = "";

    for (int i = 0; i < 26; i += 1) {
        int x = Result(intervals, here[i], m);

        if (x != -1) {
            while (x--) {
                result += char(i + 'a');
            }
            cout << result << '\n';
            return 0;
        } else {
            for (int j = 0; j < (int)here[i].size(); j += 1) {
                result += char(i + 'a');
                intervals.push_back(here[i][j]);
            }
            sort(intervals.begin(), intervals.end());
        }
    }
    return 0;
}
