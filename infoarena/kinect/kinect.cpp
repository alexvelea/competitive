#include <cstdio>
#include <fstream>

#include <algorithm>
#include <set>

using namespace std;
	
 	ifstream in("kinetic.in");
	ofstream out("kinetic.out");
 
	#define MaxChar 1000000
	#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

	long CharB=MaxChar-1;
	char Buffer [ 2*MaxChar ];

	void cit ( long long &a )
	{
	    bool ok=0;
	    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
		;
	    if ( Buffer[ CharB ] == '-' ){
		CharB++;
		ok=1;
	    }
	    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
		;
	    if ( ok ){
		a=-a;
	    }
	}


    #define max_query 200005
	#define max_segm 505 

    #define fi first
	#define se second

	long long i;
	long long nr_segm, nr_query;
	long long q,x,y,t;

	long long Rez[max_query];

	set < pair<long long,long long> > Set;
	pair<long long,long long> Over [ 4*max_segm*max_segm ];

	long long max ( long long a, long long b ){
		if ( a > b )
			return a;
		return b;
	}
	long long min ( long long a, long long b ){
		if ( a < b )
			return a;
		return b;
	}

	struct task {
		long long val, t, ind,tip;
		task ( long long a, long long b, long long c, long long d ){
			val=a;
			t=b;
			ind=c;
			tip=d;
		}
		task () {
			val=t=ind=0;
		}
	} Query [ 5*max_query ];

	struct segment {
		long long a,b;
	} Segm[ max_segm ], Segm_copy[ max_segm ];

bool mysort_query ( task a, task b ){
	if ( a.t == b.t ){
		if ( a.tip == b.tip ){
			return a.ind < b.ind;
		}
		return a.tip < b.tip;
	}
	return a.t < b.t ;
}
bool mysort_segm ( segment a, segment b ){
	return a.a < b.a;
}

pair<long long,long long> make_overtake ( segment a, segment b ){
	// cand a o sa fie depasit de b.
	pair<long long,long long> rez;
	if ( a.b >= b.b ){
		rez.fi = -1;
	}
	else{
    	if ( ( a.a - b.a ) % ( b.b-a.b ) != 0 ){
			rez.fi = ( a.a - b.a ) / ( b.b-a.b ) +1 ;
		}
		else{
			rez.fi = ( a.a - b.a ) / ( b.b-a.b );
		}
	}
	return rez;
}

long long calc_time ( segment s, long long t ){
	return s.a+s.b*t;
}

long long bs ( long long val, long long time ){
	long long ind = ( 1<<10 );
	long long rez=0;
	for ( ; ind; ind>>=1 ){
		if ( ind+rez <= nr_segm ){
	        if ( calc_time ( Segm[ rez+ind ], time ) <= val ){
				rez+=ind;

			}
		}
	}
	return rez;
}

int main(){

	verf;

 	cit( nr_segm );
	cit ( q );

	for ( i=1; i<= nr_segm; ++i ){
		cit ( Segm[i].a );
		cit ( Segm[i].b );
	}

	for ( i=1; i<= q; ++i ){
		cit ( x );
		cit ( y );
		cit ( t );
		if ( x > y )
			swap ( x,y );
		Query [++nr_query] = task ( x-1,t,i,2 );
		Query [++nr_query] = task ( y,t,i,1 );
	}


	sort ( Segm +1, Segm +nr_segm +1, mysort_segm );
	for ( i=1; i<=nr_segm; ++i ){
		Segm_copy[i]=Segm[i];
	}
	// [n] e cel mai tare .. [1] e cel mai slab la un moment 't' 

	// adaugam in set eventurile de depasiri.
	for ( i=1; i<nr_segm; ++i ){
 		pair <long long,long long> aux;
		aux = make_overtake ( Segm[i+1], Segm[i] );
		aux.second=i;
		if ( aux.fi != -1 ){
			Set.insert ( aux );
		}
		/* aux . fi = timpul cand 
		aux . se va depasi pe urmatorul segment. */
	}

	int xxx=0;
	while ( !Set.empty() ){
 		pair <long long,long long> act;
 		act = *( Set.begin() );
        
		xxx++;
		Query [++nr_query] = task ( act.se, act.fi, xxx, 0 );
		if ( nr_query > 3*max_query -1 )
			return -1;
		// elementul i va depasi elementul i+1
		// scoatem din for cate ceva
		for ( i = max ( 1, act.se-1 ); i <= min ( nr_segm-1, act.se+2 ); i++ ){
			pair <long long,long long> aux;
			aux = make_overtake ( Segm[i+1], Segm[i] );
			aux.second = i;
			if ( aux.fi != -1 ){
				Set.erase ( aux );
			}
		}
		swap ( Segm[ act.se ], Segm[ act.se+1 ] );
		// acum inseram inapoi ^^
 		for ( i = max ( 1, act.se-1 ); i <= min ( nr_segm-1, act.se+2 ); i++ ){
			pair <long long,long long> aux;
			aux = make_overtake ( Segm[i+1], Segm[i] );
			aux.second = i;
			if ( aux.fi != -1 ){
				Set.insert ( aux );
			}
		}          
	}

	for ( i=1; i<=nr_segm; ++i ){
		Segm[i] = Segm_copy[i];
	}

	// am terminat cu depasirile.
 	sort ( Query+1, Query + nr_query + 1, mysort_query );
	

	for ( i=1; i<= nr_query; ++i ){
 		if ( Query [ i ].tip == 0 ){
			swap ( Segm[ Query[i].val ], Segm[ Query[i].val+1 ] );
		}
		else{
			long long aux = bs ( Query[i].val , Query[i].t );
			if ( Query[i].ind > q )
				return -1;
			if ( Query[i].tip == 1 )
				Rez[ Query[i].ind ] += aux;
			else
				Rez[ Query[i].ind ] -= aux;
		}
	}

	for ( i=1; i<=q; ++i ){
		out<<Rez[i]<<"\n";
	}
	return 0;
}
