#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	srand(time(NULL));
    freopen ("balans.in","w",stdout);
    printf("150 150\n");
    printf("%d %d\n", (rand()%150)+1, (rand()%150)+1 );
    for ( int i=1; i<=150*150; i++ )
    {
        printf("%d ",(rand()%1000)+1);
    }
    return 0;
}
