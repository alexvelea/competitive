#include <algorithm>
#include <fstream>
using namespace std;

#define fi first
#define se second
#define max_n 200005
#define max_m 200005
#define max_q 100005
#define pb push_back

struct edge{
	int a,b,c;
	edge(){
		a=b=c=0;
	}
	edge( int _a, int _b, int _c ){
		a=_a;
		b=_b;
		c=_c;
	}
	int other( int nod ){
		return a+b-nod;
	}
	bool operator < ( const edge E ) const{
		return c>E.c;
	}
} Edge[max_m];

struct query{
	int nod,target,ind,it;
	query( int _it, int _nod, int _target, int _ind ){
		it=_it;
		nod=_nod;
		target=_target;
		ind=_ind;
	}
	query(){
		nod=target=ind=it;
	}
} Rez[max_q];

bool sort_ind( query a, query b ){
	return a.ind<b.ind;
}
bool sort_it( query a, query b ){
	return a.it<b.it;
}
 
int n,m,q;
int a,b,c;
int i,j,l,p,st;
int Father[max_n], Size[max_n], Inc[max_n];
 
int get_father( int nod ){
	if( nod != Father[nod] )
		Father[nod]=get_father( Father[nod] );
	return Father[nod];
}

void merge(){
	int next=1,st,dr;
	for( ; next<=q; ){
		st=next;
		dr=st;
		while( dr<=q && Rez[dr].ind == Rez[st].ind )
			++dr;
		next=dr;
		dr--;
		while( st<dr ){
			while( st<=dr && Inc[st]==0 )
				++st;
			while( dr>=st && Inc[dr]==1 )
				--dr;
			if( st < dr ){
				swap( Rez[st], Rez[dr] );
				swap( Inc[st], Inc[dr] );
			}
			st++;
			dr--;
		}
	}
	return ;
}

ifstream in("luff.in");
ofstream out("luff.out");

#define MaxBuffSize 1000000
int CharAct=MaxBuffSize-1;
char Buffer[MaxBuffSize];
#define verf ((++CharAct==MaxBuffSize)?(in.read(Buffer,MaxBuffSize),CharAct=0):(1)) 
void cit( int &n ){
	n=0;
	while(!( Buffer[CharAct] >= '0' && Buffer[CharAct] <= '9' ))
		verf;
	while( Buffer[CharAct] >= '0' && Buffer[CharAct] <= '9' ){
		n*=10;
		n+=Buffer[CharAct]-'0';
		verf;
	}
	return ;
}

int main(){
	verf;
	cit(n);cit(m);cit(q);
	for( i=1; i<=m; ++i ){
		cit(a);cit(b);cit(c);
		Edge[i]=edge( a,b,c );
	}
	sort( Edge+1, Edge+m+1 );
	for( p=0; (1<<p) <= m; ++p )
		;
	for( i=1; i<=q; ++i ){
		cit(a);
		cit(b);
		Rez[i]=query(i,a,b,0);
	}
	for( --p; p>=0; --p ){
		l=(1<<p);
		for( i=1; i<=n; ++i ){
			Father[i]=i;
			Size[i]=1;
		}
		st=1;
		for( i=1; i<=m; ++i ){
			// punem muchia 
			a = Edge[i].a;
			b = Edge[i].b;
			a=get_father(a);
			b=get_father(b);
			if( a!=b ){
				if( Size[a]>Size[b] ){
					Size[a]+=Size[b];
					Father[b]=a;
				}else{
					Size[b]+=Size[a];
					Father[a]=b;
				}
			}
			// facem queryurile
			while( st<=q && l+Rez[st].ind == i ){
				if( Size[get_father(Rez[st].nod)] >= Rez[st].target )
					;
				else
					Inc[st]++;
				st++;
			}          
		}
		merge();
		for( i=1; i<=q; ++i ){
			if( Inc[i] )
				Rez[i].ind+=l;
			Inc[i]=0;
		}
	}
	sort( Rez+1, Rez+q+1, sort_it );
	for( i=1; i<=q; ++i ){
		Rez[i].ind++;
		if( Rez[i].ind > m )
			out<<"-1\n";
		else
			out<<Edge[ Rez[i].ind ].c<<"\n";
	}
	return 0;
}
