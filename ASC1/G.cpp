#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 121111;

struct T
{
	int a, b;
	int id;
	friend bool operator <(T t0, T t1)
	{
		if(t0.a == t1.a)
			return t0.b > t1.b;
		return t0.a < t1.a;
	}
}t[N];

int dp[N];
int pre[N];

int main()
{
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> t[i].a >> t[i].b;
		t[i].id = i;
	}
	sort(t+1, t+n+1);
	int r = 1;
	dp[0] = 0;
	t[0].a = t[0].b = -1;
	for(int i = 1; i <= n; i++)
	{
		int left = 0, right = r;
		while(left+1 < right)
		{
			int mid = (left+right)>>1;
			if(t[dp[mid]].b < t[i].b)
				left = mid;
			else right = mid;
		}
		//cout << i << ' ' << left << '\n';
		pre[i] = dp[left];
		if(left+1 == r)
		{
			pre[i] = dp[left];
			dp[r++] = i;
		}
		else if(t[i].b < t[dp[left+1]].b)
		{
			dp[left+1] = i;
		}
	}
	cout << r-1 << '\n';
	vector <int> ans;
	for(int i = dp[r-1]; i; i = pre[i])
	{
		ans.push_back(t[i].id);
	}
	for(int i = ans.size()-1; i >= 0; i--)
	{
		cout << ans[i];
		if(i) cout << ' ';
	}
	cout << '\n';
}