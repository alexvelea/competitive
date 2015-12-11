#include <cstdio>

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define fi first
#define se second.first
#define th second.second
#define mp make_pair
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

#define max_n 200005

long long Rez[max_n];

struct stare{
	int color,nr_noduri,last_update;
	long long sum;
	stare(){
		color=nr_noduri=last_update=sum=0;
	}
	stare( int a, int b, int c, long long d ){
		color=a;
		nr_noduri=b;
		last_update=c;
		sum=d;
	}
	stare( int a,int b ){
		color=a;
		nr_noduri=last_update=sum=b;
	}
	void update( int deep ){
		if( deep!=last_update ){ 
			sum += nr_noduri*(last_update-deep);
			last_update=deep;
		}
	}
	void merge( int deep, stare st ){
		update( deep );
		st.update(deep);
		Rez[color] += 1LL*nr_noduri*st.sum + 1LL*st.nr_noduri*sum;
		nr_noduri += st.nr_noduri;
		sum += st.sum;
	}
	bool operator <( const stare lr ) const{
		if( color != lr.color )
			return color<lr.color;
		if( nr_noduri != lr.nr_noduri )
			return nr_noduri < lr.nr_noduri;
		if( last_update != lr.last_update )
			return last_update < lr.last_update;
		return sum < lr.sum;
	}
	void debug() const{
		printf("%d\t%d\t%d\t%lld\n",color,nr_noduri,last_update,sum);
	}
} ;

vector<int> Vertex[max_n];
set< stare > Set[max_n];
bool Viz[max_n];
int Color[max_n], Deep[max_n];
int n,k,i,a,b;

void solve( int nod ){
	int ind;
	Viz[nod] = 1;
	ind = nod;
	Set[nod].insert( stare( Color[nod],1,Deep[nod],0 ) );
	FORIT( it, Vertex[ nod ] ){
		if( !Viz[*it] ){
			Deep[*it]=Deep[nod]+1;
			solve( *it );
			if( Set[ind].size() < Set[*it].size() )
				ind=*it;
		}
	}
	stare target;
	set<stare> :: iterator it_target;
	swap( Set[ind],Set[nod] );
	FORIT( it, Vertex[nod] ){
 		if( Deep[*it] > Deep[nod] ){
			FORIT( it_set, Set[*it] ){
				target = stare( it_set->color, -1 );
                it_target = Set[nod].lower_bound( target );
				if( it_target == Set[nod].end() || it_target->color != target.color ){
					// adaugam 
					Set[nod].insert( *it_set );
				}else{
					// facem update
					target=*it_target;
					Set[nod].erase( it_target );
					target.merge( Deep[nod], *it_set );
					Set[nod].insert( target );
				}
			}
			Set[*it].erase( Set[*it].begin(), Set[*it].end() );
		}
	}
/*	FORIT( it,Set[nod] ){
		it->debug();
	}*/
}

int main(){
	freopen("kdist.in","r",stdin);
	freopen("kdist.out","w",stdout);
 	scanf("%d %d", &n, &k );
	for( i=1; i<n; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[a].pb(b);
		Vertex[b].pb(a);
	}
	for( i=1; i<=n; ++i ){
		scanf("%d", &a );
		Color[i]=a;
	}
	solve(1);
	for( i=1; i<=k; ++i ){
		printf("%lld\n",Rez[i]);
	}
	return 0;
}
