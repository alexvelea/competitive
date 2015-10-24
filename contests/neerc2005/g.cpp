//Problem g @ 14-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    string txt; cin >> txt;
    stack<int> st;
    for (int i = 0; i < int(txt.size()); ++i) {
        if (txt[i] == '<') {
            if (txt[i + 1] == '/') {
                st.pop();
            } else if (txt[i + 1] == 'U') {
                st.push(+1);
            } else {
                st.push(-1);
            }
            while (txt[i] != '>') {
                ++i;
            }
        } else {
            if (st.size() == 0) {
                cout << txt[i];
            } else if (st.top() == +1) {
                // up
                if (txt[i] >= 'A' and txt[i] <= 'Z') {
                    cout << char(txt[i]);
                } else {
                    cout << char(txt[i] - 'a' + 'A');
                }
            } else {
                 if (txt[i] >= 'A' and txt[i] <= 'Z') {
                    cout << char(txt[i] - 'A' + 'a');
                } else {
                    cout << char(txt[i]);
                }
            }
        }
    }
	return 0;
}
