#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

	#define pb push_back
	#define max_n 20
	
	vector<int> T[max_n];
	vector<int> C[max_n];

	int n,a,b,i,j,total,total_ok,t;
	int nr_s,Sol[30],nr;

	bool Viz[max_n];


	int Nr[max_n];

	struct suma {
		int head, nrel, El[30];
	} S[max_n][ 10000 ];

void sort ( suma &a ){
	for ( i=1; i< a.nrel; i++ ){
		for ( j=i+1; j<= a.nrel; j++ ){
			if ( a.El[i] > a.El[j] ){
				swap ( a.El[i], a.El[j] );
			}
		}
	}                                     
	return ;
}

void back ( int, int, int );

suma act;

void df ( int nod ){

	Viz[nod]=1;
	int i;
	C[nod].clear();
	for ( i=0; i<T[nod].size(); i++ ){
		if ( !Viz [ T[nod][i] ] ){
			df( T[nod][i] );
			C[nod].pb( T[nod][i] );
		}
	}

	// facem sumele acum
    act= S[nod][0];
	for ( i=0; i< (1<< ( C[nod].size() ) ); ++i ){
		back ( i, 0, nod );	
	}
}


void back ( int cod, int a, int nod ){
 	if ( a == C[nod].size() ) {
        	act.head++;
			act.nrel++;
			act.El[ act.nrel ] = act.head;
			sort ( act );
			Nr[nod]++;
			S[nod][ Nr[nod] ] = act;
			return ;
		} 
	
	int nod2= C[nod][a];
	suma init = act;
 
	for ( int j=1; j <= Nr[ nod2 ]; j++ ){
		// schimbat act-ul
		// care reprezinta suma care o sa intre in "sumele lui nod".
		if ( cod & ( 1<<a ) ){
			act.head+=S[nod2][j].head;
			int ok=0;
			for ( int l=1; l<=S[nod2][j].nrel; l++ ){
				if ( S[nod2][j].El[l] != S[nod2][j].head || ok ){
					// bagam la suma
					act.nrel++;
					act.El[ act.nrel ] = S[nod2][j].El[l];
				}
				else{
					ok=1;
				}
			}
		}
		else{
			// bagam tot 
			for ( int l=1; l<=S[nod2][j].nrel; l++ ){
				act.nrel++;
				act.El[ act.nrel ] = S[nod2][j].El[l];
			}
		}
		back ( cod, a+1, nod );
   		act=init;	
	}
}

void bt ( int suma, int m ){

    if ( suma == n ){
		total++;
		// cautam daca exista suma actuala
		int i=1;
		for ( i=1; i<=Nr[1]; i++ ){
			int ok=1;
			for ( j=1; j <= S[1][i].nrel && ok ; j++ ){
				if ( Sol[j] != S[1][i].El[j] ){
					ok=0;
				}
			}
			if ( ok ){
				total_ok++;
				return ;
			}
		}
		return ;
	}

	nr++;
	for ( int i=m; i+suma<=n; i++ ){
    	Sol[nr]=i;
		bt ( suma+i, i );
	}
	nr--;
	return ;
}

int main(){

    freopen ("avd.in","r",stdin);
	freopen ("avd.out","w",stdout);

	scanf ("%d", &t );
	for ( ; t; t-- ){
		scanf ("%d", &n );
		for ( i=1; i<n; i++ ){
			scanf ("%d %d", &a, &b );
			T[a].pb(b);
			T[b].pb(a);
		}

		df ( 1 );
		total=0;
		total_ok=0;
		nr=0;
/*		for ( i=1; i<=n; i++ ){
			printf("%d\n",i);
			for ( j=1; j<=Nr[i]; j++ ){
				printf("%d\t%d\t",S[i][j].head,S[i][j].nrel);
				for ( int l=1; l<= S[i][j].nrel; l++ )
					printf("%d ",S[i][j].El[l] );
				printf("\n");
			}
		}*/
		bt ( 0,1 );

		
		printf("%.5lf\n",double( 1.0*total_ok/total) );
//		printf("%d %d\n",total,total_ok);

		// clear the "data"
		for ( i=1; i<=n; i++ ){
			Viz[i]=0;
			T[i].clear();
			Nr[i]=0;
		}
	}

	return 0;
}
