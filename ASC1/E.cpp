#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MaxLen = 33;
const int Block = 10000;
struct BigInt
{
	int top;
	int b[MaxLen];
	inline BigInt()
	{
		top = 0;
		memset(b, 0, sizeof(b));
	}
	inline BigInt(int x)
	{
		top = 0;
		memset(b, 0, sizeof(b));
		while(x > 0)
		{
			b[top++] = x%Block;
			x /= Block;
		}
	}
	inline BigInt(string s)
	{
		int len = s.size();
		int ts = 0, tl = 1;
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
		if(!obj.top) cout << 0;
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

int MOD;
const int N = 32;
struct Matrix
{
	int num[N][N];
	int r, c;
	inline Matrix()
	{
		r = c = 0;
		memset(num, 0, sizeof(num));
	}
	inline Matrix(int ir, int ic)
	{
		r = ir; c = ic;
		memset(num, 0, sizeof(num));
	}
	friend Matrix operator *(Matrix A, Matrix B)
	{
		Matrix ret(A.r, B.c);
		for(int i = 0; i < A.r; i++)
			for(int j = 0; j < B.c; j++)
				for(int k = 0; k < A.c; k++)
				{
					ret.num[i][j] += A.num[i][k]*B.num[k][j];
					ret.num[i][j] %= MOD;
				}
		return ret;
	}
};

inline Matrix qpow(Matrix A, BigInt B)
{
	Matrix ret(A.r, A.c);
	for(int i = 0; i < A.r; i++)
		ret.num[i][i] = 1;
	Matrix T = A;
	while(B.top)
	{
		if(B.b[0]&1)
			ret = ret*T;
		T = T*T;
		B = B/2;
	}
	return ret;
}

int main()
{
	freopen("nice.in", "r", stdin);
	freopen("nice.out", "w", stdout);
	ios::sync_with_stdio(false);
	BigInt N;
	int m;
	cin >> N >> m >> MOD;
	Matrix S(1, (1<<m));
	for(int i = 0; i < (1<<m); i++)
		S.num[0][i] = 1;
	Matrix step((1<<m), (1<<m));
	for(int i = 0; i < (1<<m); i++)
		for(int j = 0; j < (1<<m); j++)
		{
			step.num[i][j] = 1;
			for(int k = 0; k < m; k++)
			{
				int calc = ((i>>k)&1) + ((j>>k)&1);
				calc += ((i>>(k+1))&1) + ((j>>(k+1))&1);
				if(!calc || calc == 4)
					step.num[i][j] = 0;
			}
		}
	Matrix T = S*qpow(step, N-1);
	int ans = 0;
	for(int i = 0; i < m; i++)
		ans += T.num[0][i];
	cout << ans%MOD << '\n';
	return 0;
}