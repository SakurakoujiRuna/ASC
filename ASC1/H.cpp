#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 121;
int prime[N];
int matrix[N][N];

const int MaxLen = 23;
const int Block = 10000;
struct BigInt
{
	int top;
	int b[MaxLen];
	BigInt()
	{
		top = 0;
		memset(b, 0, sizeof(b));
	}
	BigInt(int x)
	{
		top = 0;
		memset(b, 0, sizeof(b));
		while(x > 0)
		{
			b[top++] = x%Block;
			x /= Block;
		}
	}
	BigInt(string s)
	{
		top = 0;
		int len = s.size();
		int ts = 0, tl = 1;
		memset(b, 0, sizeof(b));
		for(int i = len-1; i >= 0; i--)
		{
			ts = ts + tl*(s[i]-'0');
			tl *= 10;

			if(tl == Block)
			{
				b[top++] = ts;
				tl = 1;
				ts = 0;
			}
		}
		b[top++] = ts;
		while(top && !b[top-1])
			top--;
	}
	friend istream& operator >>(istream& in, BigInt& obj)
	{
		string s; in >> s;
		obj = BigInt(s);
		return in;
	}
	friend ostream& operator <<(ostream& out,const BigInt& obj)
	{
		if(!obj.top) out << 0;
		else
		{	
			out << obj.b[obj.top-1];
			for(int i = obj.top-2; i >= 0; i--)
				for(int j = Block/10; j > 0; j /= 10)
					out << obj.b[i]/j%10;
		}
		return out;
	}

	friend BigInt operator +(BigInt A, const BigInt &B)
	{
		A.top = max(A.top, B.top)+1;
		for(int i = 0; i < B.top; i++)
			A.b[i] += B.b[i];
		for(int i = 0; i < A.top; i++)
			if(A.b[i] >= Block)
			{
				A.b[i] -= Block;
				A.b[i+1]++;
			}
		if(!A.b[A.top-1])
			A.top--;
		return A; 
	}
	friend BigInt operator -(BigInt A, const BigInt &B) // A >= B
	{
		for(int i = 0; i < A.top; i++)
		{
			if(A.b[i] < B.b[i])
			{
				A.b[i+1]--;
				A.b[i] += Block;
			}
			A.b[i] -= B.b[i];
		}
		while(A.top > 0 && !A.b[A.top-1])
			A.top--;
		return A;
	}
	friend BigInt operator *(const BigInt& A, const BigInt &B)
	{
		BigInt ret;
		ret.top = A.top+B.top+1;
		for(int i = 0; i < A.top; i++)
			for(int j = 0; j < B.top; j++)
			{
				ret.b[i+j] += A.b[i]*B.b[j];
				if(ret.b[i+j] >= Block)
				{
					ret.b[i+j+1] += ret.b[i+j]/Block;
					ret.b[i+j] %= Block;
				}
			}
		for(int i = 0; i < ret.top; i++)
			if(ret.b[i] >= Block)
			{
				ret.b[i+1] += ret.b[i]/Block;
				ret.b[i] %= Block;
			}
		while(ret.top && !ret.b[ret.top-1])
			ret.top--;
		return ret;
	}
	friend BigInt operator /(BigInt A, const int &den) // B <= 2*1e5
	{
		for(int i = A.top-1; i >= 0; i--)
		{
			if(i)
				A.b[i-1] += Block*(A.b[i]%den);
			A.b[i] /= den;
		}
		for(int i = 0; i < A.top; i++)
			if(A.b[i] >= Block)
			{
				A.b[i+1] += A.b[i]/Block;
				A.b[i] %= Block;
			}
		while(A.top && !A.b[A.top-1])
			A.top--;
		return A;
	}
};

int main()
{
	freopen("rsa.in", "r", stdin);
	freopen("rsa.out", "w", stdout);
	ios::sync_with_stdio(false);
	int pid = 0;
	for(int i = 2; pid < 100; i++)
	{
		bool flag = true;
		for(int j = 2; j*j <= i; j++)
			if(!(i%j)) flag = false;
		if(flag) prime[pid++] = i;
	}
	int n, m; cin >> n >> m;
	memset(matrix, 0, sizeof(matrix));
	for(int i = 0; i < m; i++)
	{
		int x; cin >> x;
		for(int j = 0; j < n; j++)
			while(!(x%prime[j]))
			{
				matrix[j][i] ^= 1;
				x /= prime[j];
			}
	}

	/*
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			cout << matrix[i][j] << ' ';
		cout << '\n';
	}
	*/
	int r = 0, j = 0;
	
	for(int i = 0; i < n && j < m; i++, j++)
		if(matrix[i][j])
		{
			for(int k = i+1; k < n; k++)
			{
				for(int t = j+1; t < m; t++)
					if(matrix[k][j])
						matrix[k][t] ^= matrix[i][t];
				matrix[k][j] = 0;
			}
			r++;
		}
		else
		{
			int flag = 0;
			for(int k = i+1; k < n; k++)
				if(matrix[k][j]) flag = k;
			if(flag)
			{
				for(int k = j; k < m; k++)
					swap(matrix[i][k], matrix[flag][k]);
				for(int k = i+1; k < n; k++)
				{
					for(int t = j+1; t < m; t++)
						if(matrix[k][j])
							matrix[k][t] ^= matrix[i][t];
					matrix[k][j] = 0;
				}
				r++;
			}
			else i--;
		}
	//cout << r << '\n';
	BigInt ans(1);
	for(int i = 0; i < m-r; i++)
		ans = ans*BigInt(2);
	cout << ans-BigInt(1) << '\n';
	return 0;
}