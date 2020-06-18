#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, b, f; cin >> n >> b >> f;
        
        int num_batches = (n + 15) / 16;
        vector<int> batch_len;
        vector<int> num_good_here(num_batches);

        {
            int aux = n;
            while (aux > 0) {
                batch_len.push_back(min(aux, 16));
                aux -= 16;
            }
        }

        for (int i = 0; i < n; i += 1) {
            cout << (!!(i & 16));
        }
        cout << endl;

        string s; cin >> s;
        for (int i = 0, current = 0, batch_num = 0; i < (int)s.size(); current ^= 1, batch_num += 1) {
            while (i < (int)s.size() and s[i] == '0' + (current)) {
                num_good_here[batch_num] += 1;
                i += 1;
            }
        }

        // testing out stuff
        string received[4];
        for (int j = 0; j < 4; j += 1) {
            string s = "";
            for (int i = 0; i < n; i += 1) {
                s += (!!(i & (1 << j))) + '0';
            }

            cout << s << endl;
            string x; cin >> x; received[j] = x;
        }

        int start_index = 0;
        for (int i = 0; i < num_batches; i += 1) {
            vector<int> current_numbers = {};
            int num_here = num_good_here[i];
//            cerr << "Num here: ... " << num_here << '\n';
            for (int j = 0; j < num_here; j += 1) {
                int x = 0;
                for (int l = 0; l < 4; l += 1) {
                    x += ((received[l][start_index + j]) - '0') << l;
                }
                current_numbers.push_back(x);
//                cerr << "Inserting: " << x << '\n';
            }

            for (int p = 0; p < batch_len[i]; p += 1) {
                bool ok = false;
                for (auto& itr : current_numbers) {
                    if (itr == p) { 
                        ok = true;
                    }
                }

                if (ok == false) {
                    cout << i * 16 + p << ' ';
                }
            }

            start_index += num_here;
        }

        cout << '\n';
        string x; cin >> x;
    }
}
