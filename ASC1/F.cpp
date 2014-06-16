#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 311;
const double PI = 4*atan(1);
const double eps = 1e-6;
vector <pair<int, double> > edge[N];

queue <int> Q;
bool inq[N];
int cnt[N];
double f[N];
inline bool SPFA(int n, int m)
{
	while(!Q.empty())
		Q.pop();
	for(int i = 0; i < n; i++)
		f[i] = 0.0;
	memset(inq, true, sizeof(inq));
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < n; i++)
		Q.push(i);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop(); inq[x] = false;
		for(int i = 0; i < edge[x].size(); i++)
			if(f[x]+edge[x][i].second+eps < f[edge[x][i].first])
			{
				cnt[edge[x][i].first] = cnt[x] + 1;
				if(cnt[edge[x][i].first] >= m+1)
					return true;
				f[edge[x][i].first] = f[x]+edge[x][i].second;
				if(!inq[edge[x][i].first])
				{
					inq[edge[x][i].first] = true;
					Q.push(edge[x][i].first);
				}
			}
		
	}
	return false;
}

double x[N], y[N], r[N];

int main()
{
	freopen("out.in", "r", stdin);
	freopen("out.out", "w", stdout);
	ios::sync_with_stdio(false);
	int n; cin >> n;
	int m = 0;
	for(int i = 0; i < n; i++)
		cin >> x[i] >> y[i] >> r[i];
	double sx, sy, sr;
	cin >> sx >> sy >> sr;
	for(int i = 0; i < n; i++)
	{
		x[i] -= sx;
		y[i] -= sy;
		r[i] += sr;
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i!=j && r[i]+r[j] > sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+eps)
			{
				double li = sqrt(x[i]*x[i] + y[i]*y[i]);
				double lj = sqrt(x[j]*x[j] + y[j]*y[j]);
				double isin = (x[i]*y[j] - y[i]*x[j])/li/lj;
				double icos = (x[i]*x[j] + y[i]*y[j])/li/lj;
				//cout << i << ' ' << j << ' ' << icos << ' ' << isin << '\n';
				if(isin > -eps)
				{
					edge[i].push_back(make_pair(j, acos(icos)));
					edge[j].push_back(make_pair(i, -acos(icos)));
					m += 2;
				}
			}

	/*
	cout << '\n';
	for(int i = 0; i < n; i++)
		for(int j = 0; j < edge[i].size(); j++)
			cout << i << ' ' << edge[i][j].first << ' ' << edge[i][j].second << '\n';
		*/
	if(SPFA(n, m))
		cout << "NO\n";
	else cout << "YES\n";
	return 0;
}