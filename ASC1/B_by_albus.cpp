#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXV = 208;
const int MAXE = MAXV*MAXV;

int V, E;

int P[MAXE], R[MAXE], L[MAXE], fre = 2;
int e[MAXE*2], f[MAXE*2], c[MAXE*2], nx[MAXE*2], h[MAXE*2];
int S, T, TOT;

inline void adde(int x, int y, int cap) {
	//cout << x << " " << y << " " << cap << endl;
	e[fre] = y; f[fre] = 0; c[fre] = cap; nx[fre] = h[x]; h[x] = fre++;
	e[fre] = x; f[fre] = 0; c[fre] = 0  ; nx[fre] = h[y]; h[y] = fre++;
}

int mk[MAXV], fa[MAXV];

bool dfs(int v) {
	//printf("v = %d\n", v);
	mk[v] = 1;
	if (v == T) return true;
	for (int k = h[v];k ;k = nx[k]) {
		int u = e[k];
		if (!mk[u] && c[k] - f[k] > 0) {
			fa[u] = k;
			if (dfs(u)) return true;
		}
	}
	return false ;
}

inline int max_flow() {
	int res = 0;

	memset(mk, 0, sizeof(mk));
	while (dfs(S)) {
		memset(mk, 0, sizeof(mk));
		int d = ~0U>>3;
		for (int v = T;v != S;v = e[fa[v]^1]) {
			d = min(d, c[ fa[v] ] - f[ fa[v] ]);
		}
		for (int v = T;v != S;v = e[fa[v]^1]) {
			f[ fa[v] ] += d;
			f[fa[v]^1] -= d;
		}
		res += d;
	}
	//printf("%d\n", res);
	return res;
}

int main() {
	scanf("%d%d", &V, &E);
	S = V + 1; T = V + 2;
	for (int i = 0;i < E;i++) {
		int x, y, l, r;
		P[i] = fre;
		scanf("%d %d %d %d", &x, &y, &l, &r);
		L[i] = l;
		adde(x, y, r - l);
		R[x] += l;
		R[y] -= l;
	}
	TOT = 0;
	for (int i = 1;i <= V;i++) {
		if (R[i] > 0) {
			adde(i, T, R[i]);
		} else if (R[i] < 0) {
			adde(S, i, -R[i]);
			TOT -= R[i];
		}
	}
	if (max_flow() == TOT) {
		puts("YES");
		for (int i = 0;i < E;i++) {
	//		cout << f[P[i]] << " " << L[i] << endl;
			printf("%d\n", f[P[i]] + L[i]);
		}
	} else {
		puts("NO");
	}
	return 0;
}
