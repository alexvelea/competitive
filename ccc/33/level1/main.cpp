#include <algorithm>
#include <iostream>
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
        int timestamp;
        double lat, lon, altitude;
        scanf("%d,%lf,%lf,%lf", &timestamp, &lat, &lon, &altitude);

        SetMx(mx_timestamp, timestamp);
        SetMn(mn_timestamp, timestamp);

        SetMx(mx_lat, lat);
        SetMn(mn_lat, lat);

        SetMx(mx_lon, lon);
        SetMn(mn_lon, lon);

        SetMx(mx_altitude, altitude);
    }

    printf("%d %d\n%.6lf %.6lf\n%.6lf %.6lf\n%.6lf\n", mn_timestamp, mx_timestamp, mn_lat, mx_lat, mn_lon, mx_lon, mx_altitude);
}
