#include <cassert>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
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
    cerr << "Reading " << name << '\n';
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
    string s;

    bool operator<(const Encounter& oth) {
        if (a != oth.a) { return a < oth.a; }
        if (b != oth.b) { return b < oth.b; }
        if (d != oth.d) { return d < oth.d; }
        assert(false);
    }

    void Print() {
        cout << a << ' ' << b << ' ' << d << ' ' << s << '\n';
    }
};

int main() {
    double mn_tresh = 1000.0;
    double mx_tresh; scanf("%lf", &mx_tresh);

    int n;
    scanf("%d", &n);

    vector<Flight> flights;
    for (int i = 0; i < n; i += 1) {
        int id; scanf("%d", &id);
        flights.push_back(ReadCSV(id));
        flights.back().GetAll();
    }

    cerr << "Done reading\n";

    vector<Encounter> ans;
    
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (i == j) {
                continue;
            }
            
            auto& A = flights[i];
            auto& B = flights[j];

            if (A.destination == B.destination) { continue; }

            for (int b_delay = 0; b_delay <= 3600; b_delay += 1) {
                int start = max(A.takeoff, B.takeoff + b_delay);
                int end = min(A.takeoff + A.all.size(), B.takeoff + b_delay + B.all.size());
                
                int a_offset = A.takeoff;
                int b_offset = B.takeoff + b_delay;
                
                string s = "";
                bool streak = false;
                int first_encounter = +1e9;
                int last_encounter = -1e9;

                auto end_streak = [&]() {
                    if (not streak) { return ;}
                    if (first_encounter == last_encounter) {
                        s += to_string(first_encounter) + " ";
                    } else {
                        s += to_string(first_encounter) + "-" + to_string(last_encounter) + " ";
                    }

                    streak = false;
                    first_encounter = +1e9;
                    last_encounter = -1e9;
                };

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

                if (s != "") {
                    s.pop_back();
                    ans.push_back({A.id, B.id, b_delay, s});
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    for (auto& itr : ans) {
        itr.Print();
    }

/*
    int mx_timestamp = -1e9;
    int mn_timestamp = +1e9;

    double mx_lat = -1e9; 
    double mn_lat = +1e9; 

    double mx_lon = -1e9; 
    double mn_lon = +1e9; 

    double mx_altitude = -1e9;
*/

/*
    for (int i = 0; i < n; i += 1) {
        int timestamp, takeoff;
        double lat, lon, altitude;
        // scanf("%d,%lf,%lf,%lf,", &timestamp, &lat, &lon, &altitude);
        scanf("%lf,%lf,%lf,", &lat, &lon, &altitude);

        flights[{string(a), string(b)}][takeoff] = 1;

        SetMx(mx_timestamp, timestamp);
        SetMn(mn_timestamp, timestamp);

        SetMx(mx_lat, lat);
        SetMn(mn_lat, lat);

        SetMx(mx_lon, lon);
        SetMn(mn_lon, lon);

        SetMx(mx_altitude, altitude);

        printf("%.9lf %.9lf %.9lf\n", x, y, z);
    }
    for (auto& itr : flights) {
        cout << itr.first.first << ' ' << itr.first.second << ' ' << itr.second.size() << '\n';
    }
*/
//    printf("%d %d\n%.6lf %.6lf\n%.6lf %.6lf\n%.6lf\n", mn_timestamp, mx_timestamp, mn_lat, mx_lat, mn_lon, mx_lon, mx_altitude);
}
