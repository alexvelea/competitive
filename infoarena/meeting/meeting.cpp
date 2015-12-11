//Problem meeting from Infoarena
// "We are drowning in information and starved for knowledge."

#include <fstream>
#include <iomanip>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("meeting.in");
ofstream out("meeting.out");

int main() {
	double x, y, z;
	in >> x >> y >> z;
	x *= 60.0;
	y *= 60.0;
	y -= x;
	out << fixed << setprecision(9) << ((y * y) - (y - z) *(y - z)) / (y * y);
	return 0;
}
