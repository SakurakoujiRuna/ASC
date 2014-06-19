#include <iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long lli;
//multiset <lli> S;

priority_queue <lli> pq;

int main()
{
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for(int i = 0; i < n; i++)
	{
		int x; cin >> x;
		pq.push(-x);
	}
	lli ans = 0;
	while(pq.size() != 1)
	{
		lli t0 = pq.top();
		pq.pop();
		lli t1 = pq.top();
		pq.pop();
		ans -= t0+t1;
		pq.push(t0+t1);
	}
	cout << ans << '\n';
	return 0;
}