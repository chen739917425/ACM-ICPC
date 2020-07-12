// ±¶Ôö (index from 1)
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
// DC3 (index from 0)
const int N = 1e5+5;
int t[N],wa[N],wb[N],sa[N],h[N];
struct DA{
    int p[20][N],rk[N],in[N],Log[N],n;
    void init(int s[], int _n) {
        n = _n;
        rep(i,0,n) in[i] = s[i] + 1;
        in[n] = 0;
    }
    void sort(int *x,int *y,int n,int m) {
        rep(i,0,m) t[i] = 0;
        rep(i,0,n) t[x[y[i]]]++;
        rep(i,1,m) t[i] += t[i-1];
        per(i,0,n) sa[--t[x[y[i]]]] = y[i];
    }
    bool cmp(int *x,int a,int b,int d) {
        return x[a] == x[b] && x[a+d] == x[b+d];
    }
    void da(int *s,int n,int m) {
        int *x = wa,*y = wb;
        rep(i,0,n) x[i] = s[i],y[i] = i;
        sort(x,y,n,m);
        for(int j=1,p=1;p<n;m=p,j<<=1) {
            p = 0;rep(i,n-j,n) y[p++] = i;
            rep(i,0,n) if(sa[i] >= j) y[p++] = sa[i] - j;
            sort(x,y,n,m);
            swap(x,y);p = 1;x[sa[0]] = 0;
            rep(i,1,n) x[sa[i]] = cmp(y,sa[i],sa[i-1],j)?p-1:p++;
        }
    }
    void cal_h(int *s,int n,int *rk) {
        int j,k = 0;
        for(int i=0;i<=n;++i) rk[sa[i]] = i;
        for(int i=0;i<n;h[rk[i++]] = k)
            for(k&&--k,j=sa[rk[i]-1];s[i+k]==s[j+k];++k);
        h[n+1] = 0;
    }
    void build() {
        in[n] = 0;
        da(in,n+1,300);
        cal_h(in,n,rk);
        Log[0] = -1;for(int i=1;i<=n;++i) Log[i] = Log[i-1] + (i==(i&(-i)));
        for(int i=1;i<=n;++i) p[0][i] = h[i];
        for(int j=1;1<<j<=n;++j) {
            int lim = n+1-(1<<j);
            for(int i=1;i<=lim;++i)
                p[j][i] = min(p[j-1][i],p[j-1][i+(1<<j>>1)]);
        }
    }
    inline int lcp(int a,int b) {
        if(a == b) return n - a;
        a = rk[a],b = rk[b];
        if(a > b) swap(a,b);++a;
        int t = Log[b-a+1];
        return min(p[t][a],p[t][b-(1<<t)+1]);
    }
    void show() {
        rep(i,1,n+1) {
            rep(j,sa[i],n+1) cout<<in[j]<<' ';cout<<endl;
        }
    }
}Da;
int main(){
	Da.init(s,n);
	Da.build();
}
