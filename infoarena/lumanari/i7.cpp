#include<stdio.h>
#include<algorithm>
using namespace std;
int n , a[200001] , c[200001];
bool ok(int med)
{
    int numar=med;
    for (int i=1 ; i<=n ; ++i)
        a[i]=c[i];
    int cnt=1;
    for (int i=n ; i>=1 && numar != 0 ; --i , --numar)
        while(a[i] < numar && cnt <= i && a[cnt] != 0)
        {
            a[i]+=a[cnt];
            if(a[i] < numar)
                ++cnt;
            else
                a[cnt]=a[i]-numar , a[i]=numar;
            if(a[cnt] == 0)
                ++cnt;
        }
    numar=med;
    for (int i=n ; i>=1 && numar != 0 ; --i , --numar)
        if(a[i] < numar)
            return 0;
    return 1;
}
int cb()
{
    int st=1 , dr=n , med , last=0;
    while(st <= dr)
    {
        med=(st+dr) >> 1;
        if(ok(med) == 1)
        {
            last=med;
            st=med+1;
        }
        else
            dr=med-1;
    }
    return last;
}
int main()
{
    freopen("lumanari.in" , "r" , stdin);
    scanf("%d" , &n);
    for (int i=1 ; i<=n ; ++i)
        scanf("%d" , &a[i]);
    sort(a+1 , a+n+1);
    for (int i=1 ; i<=n ; ++i)
        c[i]=a[i];
    printf("%d" , cb());
    return 0;
}
