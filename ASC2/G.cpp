#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 21111;

pair<double, int> p[N];
int ans[N];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	int n, m, y;
	cin >> n >> m >> y;
	int sum = 0;
	for(int i = 0; i < n; i++)
	{
		int x; cin >> x;
		ans[i] = x*m/y;
		sum += ans[i];
		p[i] = make_pair((x*m-x*m/y*y)/(double)y, i);
	}
	sort(p, p+n);
	for(int i = 0; i < m-sum; i++)
		ans[p[n-i-1].second]++;
	for(int i = 0; i < n; i++)
	{
		if(i) cout << ' ';
		cout << ans[i];
	}
	cout << '\n';
	return 0;
}