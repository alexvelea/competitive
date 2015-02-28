#include <cstdio>
#include <iostream>
using namespace std;

const int max_n=25, max_k=35, max_s=10050, mod=3210121;

int Fact[max_s], InvFact[max_s], Sum[max_s];

int El[max_n][max_k];
int Mx[max_n][max_k];

int i,j,st,rez;
int n,k,s;

void rest( int &a ){
	while( a<0 )
		a+=mod;
	a=a%mod;
}
void get_max( int &a, int b ){
	if( a<b )
		a=b;
}
int max( int a, int b ){
	if( a>b )
		return a;
	return b;
}

int pow( int a, int p ){
	int r=1;
	while( p ){
		if( p&1 )
			r=(1LL*r*a)%mod;
		a=(1LL*a*a)%mod;
		p>>=1;
	}
	return r;
}

int comb( int n, int k ){
	return (1LL*((1LL*Fact[n]*InvFact[n-k])%mod)*InvFact[k])%mod;
}

void bt( int nod, int exp ){
	if( nod == n+1 ){
		int sum=0;
		for( int i=1; i<=k; ++i )
			sum+=Mx[nod-1][i];
		if( sum<=s ){
			if( exp==1 )
				rez+=Sum[s-sum];
			else
				rez-=Sum[s-sum];
			rest(rez);
		}
		return ;
	}
	for( int i=1; i<=k; ++i )
		Mx[nod][i]=Mx[nod-1][i];
	bt( nod+1, exp );
	for( int i=1; i<=k; ++i )
		Mx[nod][i]=max(Mx[nod-1][i],El[nod][i]);
	bt( nod+1, -exp );

}

int main(){
	freopen("cowfood.in","r",stdin);
	freopen("cowfood.out","w",stdout);
	scanf("%d %d %d", &k, &s, &n );
	for( i=1; i<=n; ++i )
		for( j=1; j<=k; ++j )
			scanf("%d", &El[i][j] );
	Fact[0]=InvFact[0]=1;

	Fact[1]=1;
	for( i=2; i<=s+k; ++i )
		Fact[i]=(1LL*Fact[i-1]*i)%mod;

	InvFact[s+k]=pow(Fact[s+k],mod-2);
	for( i=s+k-1; i>=1; --i )
		InvFact[i]=(1LL*InvFact[i+1]*(i+1))%mod;
	for( i=0; i<=s; ++i ){
		Sum[i]=comb(i+k-1,k-1);
		if( i>0 )
			Sum[i]+=Sum[i-1];
		rest(Sum[i]);
	}
	bt( 1,1 );
	rez-=k*s+1;
	rest(rez);
	printf("%d\n",rez);
	return 0;
}
