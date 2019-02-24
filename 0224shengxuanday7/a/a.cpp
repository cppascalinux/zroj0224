#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,p;
int f[59][209][2];
void init()
{
	for(int i=0;i<m;i++)
	{
		int sm=0,t=i;
		if(!t)
			sm++;
		while(t)
		{
			t/=10;
			sm++;
		}
		f[sm][i][1]=1;
	}
}
void dp()
{
	for(int i=3;i<=n;i++)
		for(int j=0;j<m;j++)
		{
			f[i][j][1]=((ll)f[i][j][1]+f[i-2][j][0]+f[i-2][j][1])%mod;
			for(int k=2;k<=i-1;k++)
			{
				for(int l=0;l<m;l++)
				{
					int t1=(j-l+m)%m,t2=(l-j+m)%m;
					f[i][j][0]=(f[i][j][0]+((ll)f[k-1][l][0]+f[k-1][l][1])*(f[i-k][t1][1]+f[i-k][t2][1]))%mod;
				}
			}
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&p);
	init();
	// for(int i=1;i<=n;i++)
	// 	for(int j=0;j<m;j++)
	// 		for(int k=0;k<=1;k++)
	// 			printf("i:%d j:%d k:%d f:%d\n",i,j,k,f[i][j][k]);
	dp();
	printf("%d",(f[n][p][0]+f[n][p][1])%mod);
	return 0;
}