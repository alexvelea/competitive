#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
	
    int n;
	long long x,mx=(long long)(99999999999999999);

long long inmultire ( long long a, long long b , long long mod ){
	if ( b == 1 )
		return a;
	if ( b==0 )
		return 1;
	if ( b&1 ){
		long long aux=inmultire ( a, b/2, mod );
        aux=(aux*2)%mod;
		aux=(aux+a)%mod;
		return aux;
	}
	long long aux = inmultire ( a, b/2, mod );
	aux=(aux*2)%mod;
	return aux;
}

bool MR ( long long Num, long long Test )
{
    long long Mod=Test;
    long long m1=1,m2=1;
    long long k=0,T[40];
    Test--;
    while ( Test )
    {
        T[++k]=Test&1;
        Test>>=1;
    }
    for ( ; k; k-- )
    {
        m2=m1;
        m1=(long long) inmultire ( m1, m1, Mod );
        if ( ( m1 == 1 ) && ( m2!=1 ) && ( m2!=Mod-1 ) )
            return 0; 
        if ( T[k] )
            m1=(long long) inmultire ( m1, Num, Mod );
    }
    if ( m1!=1 )
        return 0;
    return 1;
}


bool prim ( long long val )
{
    if ( val == 1 )
        return 0;
    long Numbers[5]={2,3,5,7,61};
    for ( long i=0; i<5; i++ )
        if ( MR(Numbers[i],val)==0 && Numbers[i]!=val )
            return 0;
    return 1;
}


bool ok ( long long a, int p ){
	int rez,aux;
	rez=pow(a,double(1.0/p));
	for ( aux=rez-1; aux<=rez+2; aux++ ){
		if ( pow(aux,p) == a ){
			if ( prim ( aux ) )
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

int prime[100],nrp;
bool uber ( long long a ){
	for ( int i=2; i<=64; i++ ){
		if ( ok ( a, i ) ){
			return 1;
		}
	}
	return 0;
}

int main(){
	freopen ("ubercool.in","r",stdin);
	freopen ("ubercool.out","w",stdout);
	// calculam numerele prime
	nrp=0;
	for ( int i=2; i<=64; i++ ){
		if ( prim ( i ) )
			prime[++nrp]=i;
	}
	cin>>n;
	for ( ; n; n-- ){
		cin>>x;
		if ( x == 0 || x == 1 ){
        	cout<<"NU\n";
		}			
		else{
			if ( uber ( x ) )
				cout<<"DA\n";
			else
				cout<<"NU\n";
		}
	}
	return 0;
}
