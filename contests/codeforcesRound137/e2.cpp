#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <memory.h>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <time.h>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
using namespace std;
#define M_PI 3.14159265358979323846
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned ll
#define pii pair<int,int>
#define pll pair<ll,ll>
struct matrix
{
    ll m[53][53];
};
ll l;
matrix mult(const matrix &a,const matrix &b)
{
    matrix c;
    for (ll i=0;i<=l;i++)
    {
        for (ll j=0;j<=l;j++)
        {
            ll sum=0;
            for (ll k=0;k<=l;k++)
            {
                sum+=(a.m[i][k]*b.m[k][j])%1000000007;
                sum%=1000000007;
            }
            c.m[i][j]=sum;
        }
    }
    return c;
}

matrix sqr(const matrix &a)
{
    return mult(a,a);
}

matrix binpow(const matrix &a,ll pow)
{
    if (pow==1)
    {
        return a;
    }
    else
    {
            if ((pow%2)==0)
            {
                return sqr(binpow(a,pow/2));
            }
            else
            {
                return mult(binpow(a,pow-1),a);
            }
    }
}
ll norm(char c)
{
    if ((c>='a')&&(c<='z'))
    {return c-'a';}
    else
    {
        return c-'A'+26;
    }
}
matrix x1;
ll n,k;
int main()
{
    //freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
    cin>>n>>l>>k;
    l--;
    char a,b;
    for (ll i=0;i<=l;i++)
    {
        for (ll j=0;j<=l;j++)
        {x1.m[i][j]=1;}
    }
    for (ll i=0;i<k;i++)
    {
        cin>>a>>b;
        x1.m[norm(b)][norm(a)]=0;
    }
    if (n==1)
    {cout<<l+1<<endl;exit(0);}
    x1=binpow(x1,n-1);
    long long sum=0;
    for (ll i=0;i<=l;i++)
    {
        for (ll j=0;j<=l;j++)
        {
            sum+=x1.m[i][j];
            sum%=1000000007;
        }
    }
    cout<<sum<<endl;
    return 0;
}
