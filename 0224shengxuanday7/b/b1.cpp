#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define mod 1000000007
using namespace std;
int n;
int h[109],sm[109];
int mul[109],inv[109];
int f[109][109][109];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void initc()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	inv[n]=qpow(mul[n],mod-2);
	for(int i=n-1;i>=0;i--)
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
	//for(int i=0;i<=n;i++)
	//	printf("i:%d mul;%d inv:%d\n",i,mul[i],inv[i]);
}
int cb(int a,int b)
{
	if(b<0||b>a)
		return 0;
	return (ll)mul[a]*inv[b]%mod*inv[a-b]%mod;
}
void dp()
{
	//for(int i=0;i<=n;i++)
	//	printf("i;%d sm:%d\n",i,sm[i]);
	//printf("cb:%d\n",cb(5,3));
	for(int i=0;i<=n;i++)
		f[i][0][0]=1;
	for(int i=n-1;i>=0;i--)
		for(int j=1;j<=sm[i];j++)
			for(int k=1;k<=j;k++)
				for(int l=0;l<=j-k;l++)
					f[i][j][k]=(f[i][j][k]+(ll)cb(sm[i]-j+k,k)*f[i+1][j-k][l]%mod*mul[l]%mod*cb(k+l-1,k-1))%mod;
	//for(int i=0;i<=n-1;i++)
	//	for(int j=0;j<=n;j++)
	//		for(int k=0;k<=n;k++)
	//			if(f[i][j][k])
	//				printf("i:%d j:%d k:%d f:%d\n",i,j,k,f[i][j][k]);
	printf("%d",f[0][n][1]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",h+i);
		sm[h[i]]++;
	}
	for(int i=n;i>=0;i--)
		sm[i]+=sm[i+1];
	initc();
	dp();
	return 0;
}
