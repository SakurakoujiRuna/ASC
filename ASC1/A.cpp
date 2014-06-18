#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MaxLen = 2333;
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
	freopen("china.in", "r", stdin);
	freopen("china.out", "w", stdout);

	ios::sync_with_stdio(false);
	
	BigInt N; cin >> N;
	int flag = N.b[0]%4;
	if(flag == 0)
		cout << N/2-BigInt(1) << '\n';
	else if(flag == 2)
		cout << N/2-BigInt(2) << '\n';
	else
		cout << N/2 << '\n';
	return 0;
}