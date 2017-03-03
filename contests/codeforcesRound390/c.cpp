#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<string, int> person_id;

bool IsOk(char c) {
    return ('0' <= c and c <= '9') or ('a' <= c and c <= 'z') or ('A' <= c and c <= 'Z');
}

bool IsPerson(const string& txt) {
    return person_id.find(txt) != person_id.end();
}

vector<int> GetPersons(const string& content) {
    vector<int> ids;
    string current_string;
    int n = (int)content.size();
    for (int i = 0; i < n; i += 1) {
        if (IsOk(content[i])) {
            current_string += content[i];           
        } else {
            if (current_string.size()) {
                if (IsPerson(current_string)) {
                    ids.push_back(person_id[current_string]);
                }
            }
            current_string = "";
        }
    }

    if (current_string.size()) {
        if (IsPerson(current_string)) {
            ids.push_back(person_id[current_string]);       
        }
    }
    return ids;
}

int sender[127];
int person_in_chat[127][127];
int father[127][127];
int possible[127][127];

void Clean() {
    person_id.clear();
    for (int i = 0; i < 127; i += 1) {
        for (int j = 0; j < 127; j += 1) {
            person_in_chat[i][j] = false;
            father[i][j] = -2;
            possible[i][j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        Clean();

        int num_persons; cin >> num_persons;
        vector<string> person_name(num_persons);
        for (int i = 0; i < num_persons; i += 1) {
            string txt; cin >> txt;
            person_id[txt] = i;
            person_name[i] = txt;
        }

        int m; cin >> m;
        char t[12313]; cin.getline(t, sizeof(t));

        vector<string> initial_txt;
        for (int i = 0; i < m; i += 1) {
            char txt[127];
            cin.getline(txt, 126);
            string content = txt;
            auto persons = GetPersons(content);

            if (content[0] == '?') {
                sender[i] = -1;
            } else {
                sender[i] = persons[0];
            }

            for (auto itr : persons) {
                person_in_chat[i][itr] = true;
            }

            initial_txt.push_back(content);
        }


        auto IsPersonOk = [&](int message, int p_id) {
            auto Father = [&]() {
                if (message == 0) {
                    return 0;
                }

                for (int i = 0; i < num_persons; i += 1) {
                    if (i == p_id) {
                        continue;
                    }

                    if (possible[message - 1][i]) {
                        return i;
                    }
                }
                return -1;               
            };

            if (sender[message] == p_id) {
                return Father();
            }
            
            if (sender[message] != -1) {
                return -1;
            }

            if (person_in_chat[message][p_id] == true) {
                return -1;
            }

            if (message == 0) {
                return 0;
            }

            return Father();
        };

        for (int i = 0; i < m; i += 1) {
            for (int p = 0; p < num_persons; p += 1) {
                int f = IsPersonOk(i, p);
                if (f != -1) {
                    father[i][p] = f;
                    possible[i][p] = true;
                }
            }
        }

        int person = -1;
        for (int i = 0; i < num_persons; i += 1) {
            if (possible[m - 1][i]) {
                person = i;
            }
        }

        if (person == -1) {
            cout << "Impossible\n";
        } else {
            vector<int> senders(m);
            for (int i = m - 1; i >= 0; i -= 1) {
                senders[i] = person;
                person = father[i][person];
            }

            for (int i = 0; i < m; i += 1) {
                string txt = initial_txt[i];
                if (txt[0] == '?') {
                    txt = txt.substr(1, txt.size());
                    txt = person_name[senders[i]] + txt;
                }

                cout << txt << '\n';
            }
        }

    }
    return 0;
}

