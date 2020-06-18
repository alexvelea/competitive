#include <cassert>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

typedef long long int64;

template<typename T>
void SetMx(T& a, T b) {
    if (a < b) { a = b; }
}

template<typename T>
void SetMn(T& a, T b) {
    if (a > b) { a = b; }
}

struct FlightPoint {
    int offset;
    double lat, lon, alt;

    double x, y, z;

    void Debug() { cerr << offset << '\t' << lat << '\t' << lon << '\t' << alt << '\n'; }

    void Init() {
        double earthRadius = (6371000 + alt);
        x = earthRadius * cos(lat / 180.0 * M_PI) * cos(lon / 180.0 * M_PI);
        y = earthRadius * cos(lat / 180.0 * M_PI) * sin(lon / 180.0 * M_PI);
        z = earthRadius * sin(lat / 180.0 * M_PI);
    }
    

    bool Valid() { return alt + 1e-9 > 6000.0; }
    double Distance(const FlightPoint& oth) {
        return sqrt(
                (x - oth.x) *
                (x - oth.x) +
                (y - oth.y) *
                (y - oth.y) +
                (z - oth.z) *
                (z - oth.z)
        );
    }

};

struct Flight {
    int id;
    string origin, destination;
    int takeoff;
    vector<FlightPoint> intermediery;
    vector<FlightPoint> all;

    void GetAll() {
        all.push_back(intermediery[0]);
        for (int i = 1; i < (int)intermediery.size(); i += 1) {
            int start = all.back().offset;
            int end = intermediery[i].offset;

            auto a = intermediery[i - 1];
            auto b = intermediery[i];
            for (int timestamp = start + 1; timestamp <= end; timestamp += 1) {
                double a_weight = 1.0 - (1.0 * (timestamp - a.offset) / (b.offset - a.offset));
                double lat, lon, alt;
                lat = a_weight * a.lat + (1.0 - a_weight) * b.lat;
                lon = a_weight * a.lon + (1.0 - a_weight) * b.lon;
                alt = a_weight * a.alt + (1.0 - a_weight) * b.alt;
                all.push_back({timestamp, lat, lon, alt, 0, 0, 0});
            }
        }

        for (auto& itr : all) {
            itr.Init();
        }
    }
};

char a[100], b[100];

Flight ReadCSV(int id) {
    string name = "./flights/" + to_string(id) + ".csv";
//    cerr << "Reading " << name << '\n';
    FILE *fp;
    fp = fopen(name.c_str(), "r");
    { fscanf(fp, "%c%c%c%c\n", a, a+1, a+2, a+3); } a[4] = '\0';
    { fscanf(fp, "%c%c%c%c\n", b, b+1, b+2, b+3); } b[4] = '\0';

    int takeoff, n;
    fscanf(fp, "%d\n%d\n", &takeoff, &n);

    Flight f;
    f.id = id;
    f.origin = a;
    f.destination = b;
    f.takeoff = takeoff;

    for (int i = 0; i < n; i += 1) {
        int offset;
        double lat, lon, altitude;
        fscanf(fp, "%d,%lf,%lf,%lf,", &offset, &lat, &lon, &altitude);
        f.intermediery.push_back({offset, lat, lon, altitude, 0, 0, 0});
    }
    fclose(fp);
    return f;
}

map<pair<string, string>, map<int, int>> flights;

struct Encounter {
    int a, b;
    int d;
    vector<pair<int, int>> times;

    bool operator<(const Encounter& oth) {
        if (a != oth.a) { return a < oth.a; }
        if (b != oth.b) { return b < oth.b; }
        if (d != oth.d) { return d < oth.d; }
        assert(false);
    }

    void Print() {
        cout << a << ' ' << b << ' ' << d << ' ' << times.size() << ' ';
        for (auto& itr : times) {
            cout << itr.first << ' ' << itr.second << ' ';
        }
        cout << '\n';
    }

    Encounter Flip() const {
        Encounter oth = *this;
        oth.d *= -1;
        swap(oth.a, oth.b);
        return oth;
    }
};

map<int, vector<Encounter>> encounters;

struct RecvFrom {
    int id;
    int delay;

    bool operator<(const RecvFrom&) const {
        return false;
    }
};

struct FlightInfoRecv;

map<int, FlightInfoRecv> flight_info_recv;
priority_queue<pair<int, RecvFrom>> bfs_pq;

struct FlightInfoRecv {
    int id;
    bool got_any[3601];
    int best_time_recv[3601];
    RecvFrom parent[3601];
    bool expanded[3601];

    FlightInfoRecv() { cerr << "~"; }

    FlightInfoRecv(int id) : id(id) {
        cerr << "`";
        for (int i = 0; i <= 3600; i += 1) {
            got_any[i] = false;
            best_time_recv[i] = 1e9;
            expanded[i] = false;
        }
    }

    void InitFromScratch(int takeoff_time) {
        for (int i = 0; i <= 3600; i += 1) {
            got_any[i] = true;
            best_time_recv[i] = i + takeoff_time;
            parent[i] = RecvFrom({-1, -1});
            bfs_pq.push({-(takeoff_time + i), RecvFrom({id, i})});
        }
    }

    void UpdateFromOth(int time, int delay, RecvFrom from) {
//        cerr << "Best time -- " << best_time_recv[delay] << "\t" << delay << '\n';
        if (best_time_recv[delay] > time) {
//            cerr << "Expanding from (" << from.id << " " << from.delay << ")\t(" << id << ' ' << delay << ")\n"; 
            best_time_recv[delay] = time;
            got_any[delay] = true;
            parent[delay] = from;
            bfs_pq.push({-time, RecvFrom({id, delay})});
        }
    }

    void UpdateFromOwnDelay(int own_delay) {
        if (not got_any[own_delay]) {
            return;
        }

        if (expanded[own_delay]) {
            return;
        }

        expanded[own_delay] = true; 
        auto from = RecvFrom({id, own_delay});

        for (auto enc : encounters[id]) {
            auto delay = enc.d;
            auto oth = enc.b;
            int target_delay = own_delay + delay;

            if (0 <= (target_delay) and (target_delay) <= 3600) { }
            else { continue; }

            int target_time = best_time_recv[own_delay] - own_delay;
            int mn_time = 1e9;
            for (auto times : enc.times) {
                int start = times.first;
                int end = times.second;
                if (start <= target_time and target_time <= end) {
                    mn_time = target_time;
                    break;
                }

                if (target_time <= start) {
                    mn_time = start;
                    break;
                }
            }

            if (mn_time == +1e9) { continue; }

            mn_time += own_delay;
//            cerr << "UPdating!!\t" << oth << '\n';
            flight_info_recv[oth].UpdateFromOth(mn_time, target_delay, from);

        }
    }
};

void InitEncounters(const vector<Encounter>& _encounters) {
    for (auto& e : _encounters) {
        encounters[e.a].push_back(e);
        encounters[e.b].push_back(e.Flip());
    }
}

vector<Encounter> ComputeEncounters(int n, vector<Flight>& flights, double mn_tresh, double mx_tresh) {
    vector<Encounter> ans;
    
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (i == j) {
                continue;
            }
            
            auto& A = flights[i];
            auto& B = flights[j];

            if (A.destination == B.destination) { continue; }

            vector<pair<int, int>> times;
            bool streak = false;
            int first_encounter = +1e9;
            int last_encounter = -1e9;

            auto end_streak = [&]() {
                if (not streak) {
                    return;
                }
                times.push_back({first_encounter, last_encounter});

                streak = false;
                first_encounter = +1e9;
                last_encounter = -1e9;
            };

            for (int b_delay = 0; b_delay <= 3600; b_delay += 1) {
                times.clear();
                streak = false;
                first_encounter = +1e9;
                last_encounter = -1e9;

                int start = max(A.takeoff, B.takeoff + b_delay);
                int end = min(A.takeoff + A.all.size(), B.takeoff + b_delay + B.all.size());
                
                int a_offset = A.takeoff;
                int b_offset = B.takeoff + b_delay;
                

                for (int i = start; i < end; i += 1) {
                    auto a = A.all[i - a_offset];
                    auto b = B.all[i - b_offset];
                    double d = a.Distance(b);

                    if (a.Valid() and b.Valid()) {
                    } else { end_streak(); continue; }

                    if (mn_tresh <= d and d <= mx_tresh) {
                        first_encounter = min(first_encounter, i);
                        last_encounter = i;
                        streak = true;
                    } else {
                        end_streak();
                    }
                }

                end_streak(); 

                if (times.size()) {
                    ans.push_back({A.id, B.id, b_delay, times});
                }
            }
        }
    }
    return ans;
}

vector<Encounter> ReadFlightsFromFile(int id) {
    ifstream fin("./level6_"+to_string(id)+".flights");
    vector<Encounter> ans;
    while (1) {
        int src, dest, delay, num;
        if (fin >> src >> dest >> delay >> num) {
        } else { break; }

        Encounter e;
        e.a = src;
        e.b = dest;
        e.d = delay;

        while (num--) {
            int a, b; fin >> a >> b;
            e.times.push_back({a, b});
        }

        ans.push_back(e);
    }

    return ans;
}

int main() {
    // read test number
    int test_id; scanf("%d\n", &test_id);

    cerr << "Test id: " << test_id << '\n';

    // read 2 shits
    { scanf("%c%c%c%c ", a, a+1, a+2, a+3); } a[4] = '\0';
    { scanf("%c%c%c%c\n", b, b+1, b+2, b+3); } b[4] = '\0';

    string start = a;
    string end = b;

    double mn_tresh = 1000.0;
    double mx_tresh; scanf("%lf", &mx_tresh);

    int n;
    scanf("%d", &n);

    vector<Flight> flights;
    cerr << "Num flights: " << n << '\n';
    for (int i = 0; i < n; i += 1) {
        int id; scanf("%d", &id);
        flights.push_back(ReadCSV(id));
        flights.back().GetAll();
    }

    cerr << "Done reading\n";

    auto _encounters = ReadFlightsFromFile(test_id);
    cerr << "Got " << _encounters.size() << " encounters\n";
    InitEncounters(_encounters);

    for (auto& itr : flights) {
        flight_info_recv[itr.id] = FlightInfoRecv(itr.id);
    }

    for (auto& itr : flights) {
        if (itr.origin == start) {
            flight_info_recv[itr.id].InitFromScratch(itr.takeoff);
        }
    }

    cerr << '\n';
    cerr << "Done init!\n";

    while (bfs_pq.size()) {
        auto top = bfs_pq.top();
        bfs_pq.pop();
        auto node = top.second;
        flight_info_recv[node.id].UpdateFromOwnDelay(node.delay);
    }

    cerr << "Done computing!\n";

    map<int, int> delays;
    RecvFrom any_end;
    for (auto& itr : flights) {
        if (itr.destination != end) { continue; }

        auto& f = flight_info_recv[itr.id];
        for (int i = 0; i <= 3600; i += 1) {
            if (f.got_any[i]) {
                any_end = RecvFrom({itr.id, i});
            }
        }
    }


    vector<pair<RecvFrom, int>> history;
    while (any_end.id != -1) {
        delays[any_end.id] = any_end.delay;
        history.push_back({any_end, flight_info_recv[any_end.id].best_time_recv[any_end.delay]});
        any_end = flight_info_recv[any_end.id].parent[any_end.delay];
    }

    reverse(history.begin(), history.end());
    for (auto& itr : delays) {
        cout << itr.first << ' ' << itr.second << '\n';
    }

    cout << history[0].first.id << '\n';
    for (int i = 1; i < (int)history.size(); i += 1) {
        auto itr = history[i];
        cout << itr.second << ' ' << itr.first.id << '\n';
    }
}
