#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 1000000007
using namespace std;
int n;
ll l,r;
int f[109][259];
void dp()
{
	memset(f,0,sizeof(f));
	f[0][0]=1;
	int bit=0;
	while((1<<bit)<=r)
		bit++;
	for(int i=1;i<=n;i++)
	{
		for(int s=0;s<1<<bit;s++)
			for(int j=l;j<=r;j++)
				f[i][s|j]|=f[i-1][s];
	}
	int ans=0;
	for(int s=0;s<1<<bit;s++)
		ans+=f[n][s];
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%lld%lld",&n,&l,&r);
		dp();
	}
	return 0;
}