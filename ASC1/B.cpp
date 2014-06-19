#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 211;
const int M = 42111;
const int INF = 0x3f3f3f3f;
struct Edge
{
	int u, v;
	int flow;
	int id;
}r[M];
int Rind = 0;
int first[N], nxt[M];
inline void addEdge(int iu, int iv, int iflow, int iid)
{
	r[Rind].u = iu; r[Rind].v = iv;
	r[Rind].flow = iflow; r[Rind].id = iid;
	nxt[Rind] = first[iu]; first[iu] = Rind++;
	r[Rind].u = iv; r[Rind].v = iu;
	r[Rind].flow = 0; r[Rind].id = iid;
	nxt[Rind] = first[iv]; first[iv] = Rind++;
}

int S, T, P;
int h[N], num[N];
inline int aug(int x, int f)
{
	if(x == T) return f;
	int l = f;
	int temp = P-1;
	for(int i = first[x]; i != -1; i = nxt[i])
	{
		if(r[i].flow && (h[x] == h[r[i].v]+1))
		{
			int nf = aug(r[i].v, min(r[i].flow, l));
			l -= nf; r[i].flow -= nf;
			r[i^1].flow += nf;
			if((!l) || h[S] == P) return f-l;
		}
		if(r[i].flow) temp = min(temp, h[r[i].v]);
	}
	num[h[x]]--;
	if(num[h[x]]) { h[x] = temp+1; num[h[x]]++; }
	else h[S] = P;
	return f-l;
}

inline int SAP()
{
	memset(h, 0, sizeof(h));
	memset(num, 0, sizeof(num));
	int ret = 0; num[0] = P;
	while(h[S] < P) ret += aug(S, INF);
	return ret;
}

int ans[M];
int d[N];

int main()
{
	freopen("cooling.in", "r", stdin);
	freopen("cooling.out", "w", stdout);
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	memset(first, -1, sizeof(first));
	memset(nxt, -1, sizeof(nxt));
	memset(d, 0, sizeof(d));
	memset(ans, 0, sizeof(ans));
	for(int i = 1; i <= m; i++)
	{
		int iu, iv, l, m;
		cin >> iu >> iv >> l >> m;
		d[iu] += l;
		d[iv] -= l;
		ans[i] = l;
		addEdge(iu, iv, m-l, i);
	}
	int tot = 0;
	S = 0, T = n+1;
	P = n+2;
	for(int i = 1; i <= n; i++)
		if(d[i] > 0)
		{
			tot += d[i];
			addEdge(i, T, d[i], 0);
		}
		else addEdge(S, i, -d[i], 0);
	if(SAP() != tot)
		cout << "NO\n";
	else
	{
		cout << "YES\n";
		for(int i = 1; i < Rind; i += 2)
			ans[r[i].id] += r[i].flow;
		for(int i = 1; i <= m; i++)
			cout << ans[i] << '\n';
	}
	return 0;
}