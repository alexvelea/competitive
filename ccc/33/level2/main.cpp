#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
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

map<pair<string, string>, map<int, int>> flights;

char a[100], b[100];

int main() {
    int n;
    scanf("%d", &n);

    int mx_timestamp = -1e9;
    int mn_timestamp = +1e9;

    double mx_lat = -1e9; 
    double mn_lat = +1e9; 

    double mx_lon = -1e9; 
    double mn_lon = +1e9; 

    double mx_altitude = -1e9;

    for (int i = 0; i < n; i += 1) {
        int timestamp, takeoff;
        double lat, lon, altitude;
        scanf("%d,%lf,%lf,%lf,", &timestamp, &lat, &lon, &altitude);
        for (int i = 0; i < 4; i += 1) { scanf("%c", a + i); }
        char aux; scanf("%c", &aux);
        for (int i = 0; i < 4; i += 1) { scanf("%c", b + i); }
        scanf(",%d", &takeoff);

        flights[{string(a), string(b)}][takeoff] = 1;

        SetMx(mx_timestamp, timestamp);
        SetMn(mn_timestamp, timestamp);

        SetMx(mx_lat, lat);
        SetMn(mn_lat, lat);

        SetMx(mx_lon, lon);
        SetMn(mn_lon, lon);

        SetMx(mx_altitude, altitude);
    }

    for (auto& itr : flights) {
        cout << itr.first.first << ' ' << itr.first.second << ' ' << itr.second.size() << '\n';
    }

//    printf("%d %d\n%.6lf %.6lf\n%.6lf %.6lf\n%.6lf\n", mn_timestamp, mx_timestamp, mn_lat, mx_lat, mn_lon, mx_lon, mx_altitude);
}
