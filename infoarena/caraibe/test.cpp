#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	freopen ("caraibe.in","w", stdout);
	srand(time(NULL));
	int n = 10;
 	printf("%d\n", n);
 	n -= 2;
	while (n) {
		printf ("%d\n", rand() % (n+1));
		n--;
	}
	return 0;
}
