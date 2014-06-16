#include <iostream>
#include <cstring>
using namespace std;

const int N = 12111;
typedef long long lli;

int d[N];

int main()
{
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	memset(d, 0, sizeof(d));
	for(int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		d[u-1]++;
		d[v-1]++;
	}
	lli ans = 0;
	for(int i = 0; i < n; i++)
		ans += (lli)d[i]*d[i];
	cout << ans << '\n';
	return 0;
}