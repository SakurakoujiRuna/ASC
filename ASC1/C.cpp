#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 511111;
typedef long long lli;

int fa[N];
int f[N];
int g[N];
bool sp[N];
int use[N];

int main()
{
	ios::sync_with_stdio(false);
	freopen("grant.in", "r", stdin);
	freopen("grant.out", "w", stdout);
	int n; cin >> n;
	fa[1] = 0;
	for(int i = 2;i <= n; i++)
		cin >> fa[i];
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	//memset(ans, 0, sizeof(ans));
	memset(use, -1, sizeof(use));
	for(int i = n; i >= 1; i--)
	{
		f[i] = max(f[i],0)+g[i];
		g[i] = g[i]+1;
		if(g[i]-f[i] >= f[fa[i]])
			use[fa[i]] = i;
		f[fa[i]] = max(f[fa[i]],g[i]-f[i]);
		g[fa[i]] += f[i];
	}
	/*
	for(int i=1;i<=n;i++)
		cout<<i<<' '<<f[i]<<' '<<g[i]<<'\n';
	*/
	cout << (lli)f[1]*1000 << '\n';
	memset(sp, 0, sizeof(sp));
	for(int i = 2; i <= n; i++)
		if((!sp[fa[i]]) && use[fa[i]]==i)
		{
			cout << i << ' ';
			sp[i] = true;
		}
	cout << '\n';
	return 0;
}