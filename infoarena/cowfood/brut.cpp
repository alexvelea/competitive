#include<cstdio>
#define MOD 3210121
#define max(a,b) ((a)>(b)?(a):(b))
 
 long long modpow (long long n, int e)
 {
	     if(!e)
			         return 1;
					  
					      long long x=modpow (n,e/2);
						      x=(x*x)%MOD;
							      if(e%2)
									          x=(x*n)%MOD;
											   
											       return x;
 }
  
  long long fact[10050];
  long long mfact[10050];
  long long calcs[10050];
   
   long long choose (long long n, long long k)
   {
	       if(n<k)
			           return 0;
					       if(n==k||k==0)
							           return 1;
									    
										    return fact[n]*mfact[n-k]%MOD*mfact[k]%MOD;
   }
    
	long long calc (long long n, long long k)
	{
		    if(n<0)
				        return 0;
						    return choose (n+k-1, n);
	}
	 
	 int v[25][35];
	  
	  int k,s,n;
	  long long ret;
	   
	   void back (int x,int f,int *mx)
	   {
		       if(x==n){
				           int ss=s;
						           for(int i=0;i<k;i++)
									               ss-=mx[i];
												           if(ss==s)
															               return;
																		           if(ss>=0)
																					               ret+=f*calcs[ss];
																								           ret=(ret+MOD)%MOD;
																										           return;
																												       }
																													    
																														    back (x+1,f,mx);
																															    int nmx[35];
																																    for(int i=0;i<k;i++)
																																		        nmx[i]=max (mx[i], v[x][i]);
																																				    back (x+1,-f,nmx);
	   }
	    
		int main (void)
		{
			    freopen ("cowfood.in","r",stdin);
#ifdef INFOARENA
				    freopen ("cowfood.out","w",stdout);
#endif
					 
					     scanf ("%d%d%d",&k,&s,&n);
						  
						      fact[0]=1;
							      for(int i=1;i<s+k+5;i++){
									          fact[i]=fact[i-1]*i%MOD;
											          mfact[i]=modpow (fact[i],MOD-2);
													      }
														      for(int i=0;i<10050;i++)
																          calcs[i]=calc (i,k+1);
																		   
																		       for(int i=0;i<n;i++)
																				           for(int j=0;j<k;j++)
																							               scanf ("%d",v[i]+j);
																										    
																											    ret=calcs[s]+MOD-1-s*k;
																												    ret%=MOD;
																													 
																													     int v[35]={};
																														     back (0,1,v);
																															  
																															      printf ("%lld",(ret+MOD)%MOD);
																																      return 0;
		}
