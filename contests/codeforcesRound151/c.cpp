#include <cstdio>
using namespace std;

	int n,m,i,j,k,l;
	int B[105];

	struct ceva{
		int nr,suma;
		int val[51];
	};
	struct ceva2{
		ceva El[5000];
		int nr;
	} last,act,next;

int main(){
	scanf ("%d %d", &n, &k );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &B[i]);
	}
	k++;
	last.nr=1;
	last.El[1].nr=0;
	last.El[1].val[0]=0;
	last.El[1].suma=0;
	for ( i=1; i<=n; i++ ){
		act.nr=last.nr;
        for ( j=1; j<=last.nr; j++ ){
			act.El[j]=last.El[j];
			act.El[j].val[ ++act.El[j].nr ] = i;
			act.El[j].suma+=B[i];
		}
		int i1=1,i2=1;
		next.nr=0;
		for ( ; i1<=act.nr || i2<=act.nr; ){
			if ( (act.El[i1].suma == last.El[i2].suma) && (i2<=act.nr) && (i1<=act.nr) ){
				next.El[ ++next.nr ] = act.El[i1];
				i1++;
				i2++;
			}        
			else{
				if ( ( (act.El[i1].suma < last.El[i2].suma) || ( i2>act.nr) ) && ( i1<=act.nr ) ){
					next.El[ ++next.nr ] = act.El[i1];
					i1++;
				}
				else{
					next.El[ ++next.nr ] = last.El[i2];
					i2++;
				}
			}
		}
		if ( next.nr >= k ){
			for ( j=2; j<=k; j++ ){
            	printf("%d ",next.El[j].nr );
				for ( l=1; l<=next.El[j].nr; l++ )
					printf("%d ", B[next.El[j].val[l]]);
				printf("\n");
			}
			return 0;
		}
		last=next;

	}
	return 0;
}
