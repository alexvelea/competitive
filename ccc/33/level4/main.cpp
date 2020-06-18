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
    void Debug() { cerr << offset << '\t' << lat << '\t' << lon << '\t' << alt << '\n'; }
};

struct Flight {
    string origin, destination;
    int takeoff;
    vector<FlightPoint> intermediery;
};


char a[100], b[100];

Flight ReadCSV(int id) {
    string name = "./flights/" + to_string(id) + ".csv";
    FILE *fp;
    fp = fopen(name.c_str(), "r");
    { fscanf(fp, "%c%c%c%c\n", a, a+1, a+2, a+3); } a[4] = '\0';
    { fscanf(fp, "%c%c%c%c\n", b, b+1, b+2, b+3); } b[4] = '\0';

    int takeoff, n;
    fscanf(fp, "%d\n%d\n", &takeoff, &n);

    Flight f;
    f.origin = a;
    f.destination = b;
    f.takeoff = takeoff;

    for (int i = 0; i < n; i += 1) {
        int offset;
        double lat, lon, altitude;
        fscanf(fp, "%d,%lf,%lf,%lf,", &offset, &lat, &lon, &altitude);
        f.intermediery.push_back({offset, lat, lon, altitude});
    }
    fclose(fp);
    return f;
}

map<pair<string, string>, map<int, int>> flights;

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i += 1) {
        int timestamp, id;
        scanf("%d %d", &id, &timestamp);
//        cerr << timestamp << '\t' << id << "!!!\n";
        auto f = ReadCSV(id);
//        cerr << f.intermediery.size() << '\n';

        timestamp -= f.takeoff;
        int where = 0;
        for (int i = 1; i < (int)f.intermediery.size(); i += 1) {
            if (f.intermediery[i].offset >= timestamp) {
                where = i;
                break;
            }
        }

        auto a = f.intermediery[where - 1];
        auto b = f.intermediery[where];

        double a_weight = 1.0 - (1.0 * (timestamp - a.offset) / (b.offset - a.offset));
/*        
        cerr << timestamp << '\n';
        a.Debug();
        b.Debug();
*/
        double lat, lon, alt;
        lat = a_weight * a.lat + (1.0 - a_weight) * b.lat;
        lon = a_weight * a.lon + (1.0 - a_weight) * b.lon;
        alt = a_weight * a.alt + (1.0 - a_weight) * b.alt;
        printf("%.9lf %.9lf %.9lf\n", lat, lon, alt);
//        cerr << "\n\n";
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
        double earthRadius = (6371000 + altitude);
        double x = earthRadius * cos(lat / 180.0 * M_PI) * cos(lon / 180.0 * M_PI);
        double y = earthRadius * cos(lat / 180.0 * M_PI) * sin(lon / 180.0 * M_PI);
        double z = earthRadius * sin(lat / 180.0 * M_PI);
        printf("%.9lf %.9lf %.9lf\n", x, y, z);
    }
    for (auto& itr : flights) {
        cout << itr.first.first << ' ' << itr.first.second << ' ' << itr.second.size() << '\n';
    }
*/
//    printf("%d %d\n%.6lf %.6lf\n%.6lf %.6lf\n%.6lf\n", mn_timestamp, mx_timestamp, mn_lat, mx_lat, mn_lon, mx_lon, mx_altitude);
}
