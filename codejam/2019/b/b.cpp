#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define OUT

#ifndef OUT

int day;
vector<int> here[21];


void Reset() {
    day = 0;
    for (int i = 1; i <= 20; i += 1) {
        here[i].clear();
    }
}

void GetDay() {
    day += 1;
    if (day != 100) {
        int x = 1 + rand() % 20;
        here[x].push_back(day);
    }
}

vector<int> Inspect(int pot) {
    return here[pot];
}

void Put(int pot, int number) {
    here[pot].push_back(number);
}

bool Evaluate() {

    for (int i = 1; i <= 20; i += 1) {
        cerr << i << '\t' << here[i].size() << '\n';
    }

    int mn = here[1].size();
    for (int i = 1; i <= 20; i += 1) {
        mn = min(mn, (int)here[i].size());
    }

    int num = 0;
    int where = 0;
    for (int i = 1; i < 20; i += 1) {
        if ((int)here[i].size() == mn) {
            where = i;
            num += 1;
        }
    }

    if (num != 1) {
        cerr << "~ Multiple mins\n";
        return false;
    }

    // check for duplicates
    for (int i = 0; i < (int)here[where].size(); i += 1) {
        for (int j = i + 1; j < (int)here[where].size(); j += 1) {
            if (here[where][i] == here[where][j]) {
                cerr << "~ Duplicates\n";
                return false;
            }
        }
    }

    for (int i = 0; i  <(int)here[where].size(); i += 1) {
        if (here[where][i] == 100) {
            return true;
        }
    }

            cerr << "~ No 100\n";
    return false;
}

#endif


#ifdef OUT
void Reset() {  
}

void GetDay() {
    int x; cin >> x;
}

vector<int> Inspect(int pot) {
    cout << pot << ' ' << 0 << endl;
    int x; cin >> x;
    vector<int> vals;
    for (int i = 0; i < x; i += 1) {
        int p;
        cin >> p;
        vals.push_back(p);
    }

    return vals;
}

void Put(int pot, int number) {
    cout << pot << ' ' << number << endl;
}

bool Evaluate() {
    return true;
}


#endif

int main() {
    int t; cin >> t;
    int num_ok = 0;
    for (int T = 1; T <= t; T += 1) {
        Reset();

        vector<int> mid[11];
        pair<int, int> worst_7[9];
        int good[3];
        int num_good[3];

        int final_where = 0;

        for (int i = 1; i <= 100; i += 1) {
            GetDay();

            if (i <= 50) {
                Put(11 + i % 10, 100);
            } else if (i <= 60) {
                mid[1 + (i % 10)] = Inspect(1 + (i % 10));                
            }
            
            if (i == 61) {
/*                
                for (int j = 1; j <= 10; j += 1) {
                    cerr << mid[j].size() << '\t';
                    for (auto itr : mid[j]) {
                        cerr << itr << '\t';
                    }
                    cerr << '\n';
                }
*/                

                vector<pair<int, int>> worst;
                for (int j = 1; j <= 10; j += 1) {
                    worst.push_back({mid[j].size(), j});
                }

                sort(worst.begin(), worst.end());
                for (int i = 3; i < 10; i += 1) {
                    worst_7[i - 3] = worst[i];   
                }

                for (int i = 0; i < 3; i += 1) {
                    good[i] = worst[i].second; 
                }
            }

            if (i >= 61 and i <= 84) {
                int where = 0;
                int min = 100;
                int index = 0;
                for (int i = 0; i < 7; i += 1) {
                    if (worst_7[i].first < min) {
                        min = worst_7[i].first;
                        where = worst_7[i].second;
                        index = i;
                    }
                }

                Put(where, 100);
                worst_7[index].first += 1;
            }

            if (i >= 85 and i < 85 + 3) {
                num_good[i - 85] = Inspect(good[i - 85]).size();                
            }

            if (i == 85 + 3) {
/*                
                for (int j = 0; j < 3; j += 1) {
                    cerr << "Good -- \t" << good[j] << '\t' << num_good[j] << '\n';
                }
*/                

                vector<pair<int, int>> worst;
                for (int j = 0; j < 3; j += 1) {
                    worst.push_back({num_good[j], good[j]});
                }

                sort(worst.begin(), worst.end());
                final_where = worst[0].second;

                worst_7[7] = worst[1];
                worst_7[8] = worst[2];
            }

            if (i >= 85 + 3 and i < 100) {
                int where = 0;
                int min = 100;
                int index = 0;
                for (int i = 0; i < 9; i += 1) {
                    if (worst_7[i].first < min) {
                        min = worst_7[i].first;
                        where = worst_7[i].second;
                        index = i;
                    }
                }

                Put(where, 100);
                worst_7[index].first += 1;

//                cerr << " where: " << where << "\tmin: " << min << '\n';
            }

            if (i == 100) {
//                cerr << "Final where:\t" << final_where << '\n';
                Put(final_where, 100);
            }
        }

        bool k = Evaluate();
//        cerr << "Ok? " << k << '\n';
        num_ok += k;
    }

//    cerr << "Final results:\t" << 100.0 * num_ok / t << '\n';

    return 0;
}
