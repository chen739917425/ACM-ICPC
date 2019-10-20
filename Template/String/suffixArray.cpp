int sa[maxn], rk[maxn], height[maxn], c[maxn], y[maxn];
char s[maxn];
void SA(int n,int m=128) {
	for (int i = 0; i <= m; i++) c[i] = 0;
	for (int i = 1; i <= n; i++) c[rk[i]=s[i]]++;
	for (int i = 1; i <= m; i++) c[i] += c[i - 1];
	for (int i = n; i; i--) sa[c[rk[i]]--] = i;
	for (int k = 1, p; k <= n; k <<= 1) {
		p = 0;
		for (int i = n; i > n - k; i--) y[++p] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) y[++p] = sa[i] - k;
		for (int i = 0; i <= m; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) c[rk[i]]++;
		for (int i = 1; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i; i--) sa[c[rk[y[i]]]--] = y[i];
		p = y[sa[1]] = 1;
		for (int i = 2, a, b; i <= n; i++) {
			a = sa[i] + k > n ? -1 : rk[sa[i] + k];
			b = sa[i - 1] + k > n ? -1 : rk[sa[i - 1] + k];
			y[sa[i]] = (rk[sa[i]] == rk[sa[i - 1]]) && (a == b) ? p : ++p;
		}
		swap(rk, y);
		m = p;
	}
	int k=0;
	for (int i=1;i<=n;++i){
		if (k) k--;
		int j=sa[rk[i]-1];
		while (s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}
int mn[maxn][32],lg[maxn];
void init(int n){
	for (int i=2;i<=n;++i)
		lg[i]=lg[i-1]+((i&-i)==i);
	for (int i=1;i<=n;++i)
		mn[i][0]=height[i];
	for (int j=1;(1<<j)<=n;++j)
		for (int i=1;i+(1<<j)-1<=n;++i)
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
}
int qry(int l,int r){
	int k=lg[r-l+1];
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}
int lcp(int i,int j){
	if (i>j) swap(i, j);
	return qry(i+1,j);
}
int main() {
	scanf("%s",s+1);
	int n=strlen(s+1);
	SA(n);
	init(n);
	return 0;
}
