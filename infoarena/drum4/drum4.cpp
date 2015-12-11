#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

	#define max_n 200005

int n,m;
int i,v1,v2,v;

vector <int> G[max_n];
vector <int> GT[max_n];
vector <int> CTC[max_n];
bool Viz_f[max_n];
bool Viz_f2[max_n];
int nrc;

int S[max_n],k;
int VIZ[max_n];
int C[max_n];

void df1(int v)
{
	vector <int> :: iterator it;
	int i;
	VIZ[v]=1;
	for (it=G[v].begin();it!=G[v].end();it++)
	{
		i=(*it);
		if (VIZ[i]==0)
			df1(i);
	}
	S[++k]=v;
}

void df2(int v)
{
	vector <int> :: iterator it;
	int i;
	VIZ[v]=1;
	for (it=GT[v].begin();it!=GT[v].end();it++)
	{
		i=(*it);
		if (VIZ[i]==0)
			df2(i);
	}
	CTC[nrc].push_back(v);
}


#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    for ( ; !(Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); verf )
        ;
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
}


int main()
{
	freopen ("drum4.in","r",stdin);
	freopen ("drum4.out","w",stdout);
	verf;
	cit(n);
	cit(m);
	for (i=1;i<=m;i++)
	{
		cit(v1);
		cit(v2);
		G[v1].push_back(v2);
		GT[v2].push_back(v1);
	}
	for (v=1;v<=n;v++)
		if (VIZ[v]==0)
			df1(v);
	nrc=0;
	for (i=1;i<=n;i++)
		VIZ[i]=0;
	for (i=n;i>=1;i--)
		if (VIZ[S[i]]==0)
		{
			nrc++;
			df2(S[i]);
		}
	for (i=1;i<=nrc;i++)
	{
		for ( int it=0; it<CTC[i].size(); it++ ){
			C[ CTC[i][it] ]=i;
		}
	}
	int rez=0,rez2=0;
	for ( i=1; i<=n; i++ ){
		for ( int it=0; it<G[i].size(); it++ ){
			if ( C[i] != C[G[i][it]] ){
				Viz_f[ C[ G[i][it] ] ]=1;
				Viz_f2[ C[i] ]=1;
			}
		}                       
	}             
	for ( i=1; i<=nrc; i++ ){
		if ( Viz_f[i] == 0 )
			rez++;
		if ( Viz_f2[i] == 0 )
			rez2++;
	}
	if ( nrc == 1 ) {
		cout<<"0";
		return 0;
	}
	cout<<max(rez,rez2);
	return 0;
}
