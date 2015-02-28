#include <cstdio>
using namespace std;


int Qu[ 40000 ];
char Text[ 50 ];

int st=1,dr,mid;
int i,j,n;

void push_q ( int val ){
	printf("%d: read(%d) push(2,%d)\n",i,val,val);
	Qu[ ++dr ] = val;
}
void pop_q ( ){
	if ( mid >= st ){
		printf("%d: pop(1) write(%d)\n", i, Qu[ st ] );
		st++;
	}
	else{
        int j=st;
		printf("%d: ",i);
		for ( j=dr; j>=st; --j ){
			printf("pop(2) push(1,%d) ", Qu[ j ] );
		}
		mid = dr;
		printf("pop(1) write(%d)\n", Qu[ st ] );
		st++;
	}
}

int main(){

    freopen ("queue.in","r",stdin);
	freopen ("queue.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf("%s", &Text);
		if ( Text[ 1 ] == 'u' ){
			// incepem sa citim numarul.
			int Nr = 0;
			for ( j=10; Text[ j ] != ')'; ++j ){
				Nr *= 10;
				Nr += Text[ j ] - '0';
			}
			push_q ( Nr );
		}
		else{
			pop_q ();
		}
	}

	return 0;
}
