#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define mod 1000000007
using namespace std;
int n,tot,ans;
int h[109];
int p[109],deg[109];
int hd[109],eg[209],nxt[209];
int dep[109];
int mul[109],inv[109];
int f[109][109];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs2(int x,int fa,int &sm)
{
	dep[x]=dep[fa]+1;
	// printf("x:%d dep;%d\n",x,dep[x]);
	if(dep[x]>h[x])
		sm=0;
	int s=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs2(eg[i],x,sm);
			s++;
		}
	sm=(ll)sm*mul[s]%mod;
}
void solve()
{
	// for(int i=1;i<=n-2;i++)
	// 	printf("i:%d p:%d\n",i,p[i]);
	// fflush(stdout);
	memset(hd,0,(n+1)<<2);
	tot=0;
	priority_queue<int> pq;
	for(int i=1;i<=n-2;i++)
		deg[p[i]]++;
	for(int i=1;i<=n;i++)
		if(!deg[i])
			pq.push(i);
	for(int i=1;i<=n-2;i++)
	{
		int x=pq.top();
		pq.pop();
		ins(x,p[i]);
		ins(p[i],x);
		deg[p[i]]--;
		if(!deg[p[i]])
			pq.push(p[i]);
	}
	int x=pq.top();
	pq.pop();
	int y=pq.top();
	pq.pop();
	ins(x,y);
	ins(y,x);
	dep[0]=-1;
	for(int i=1;i<=n;i++)
	{
		int sm=1;
		dfs2(i,0,sm);
		ans=(ans+sm)%mod;
	}
}
void dfs1(int d)
{
	if(d>n-2)
	{
		solve();
		return;
	}
	for(int i=1;i<=n;i++)
	{
		p[d]=i;
		dfs1(d+1);
	}
}
void initc()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	inv[n]=qpow(mul[n],mod-2);
	for(int i=n-1;i>=0;i--)
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
}
int cb(int a,int b)
{
	if(b<0||b>a)
		return 0;
	return (ll)mul[a]*inv[b]%mod*inv[a-b]%mod;
}
void dp()
{
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
			for(int k=0;k<=j;k++)
				f[i][j]=(f[i][j]+(ll)f[i-1][j-k]*mul[k]%mod*cb(j,k))%mod;
	}
}
int solve3(int x)
{
	int sm1=0;
	for(int i=1;i<=n;i++)
		if(x!=i&&h[i]==1)
			sm1++;
	int ans=0;
	for(int i=sm1;i<=n-1;i++)
		ans=(ans+(ll)cb(n-sm1-1,i-sm1)*mul[i]%mod*f[i][n-i-1])%mod;
	return ans;
}
int solve2()
{
	dp();
	int sm0=0;
	for(int i=1;i<=n;i++)
		if(h[i]==0)
			sm0++;
	if(sm0>1)
		return 0;
	if(sm0==1)
		for(int i=1;i<=n;i++)
			if(h[i]==0)
				return solve3(i);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+solve3(i))%mod;
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",h+i);
	initc();
	if(n<=8)
	{
		dfs1(1);
		printf("%d",ans);
		return 0;
	}
	printf("%d",solve2());
	return 0;
}