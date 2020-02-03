int add(int a, int b) {if ((a += b) >= mod) a -= mod; return a < 0 ? a + mod : a;}
int mul(int a, int b) {return 1ll * a * b % mod;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
int a[maxn][maxn], x[maxn]; // 增广矩阵和解集
int Free[maxn], fnum, r; 	// 一组 合法 自由变元, Free存其下标 
void genx(int col) {
	int pre = col;
	fnum = 0;
	for(int i=r-1,p;i>=0;--i) {
		for(int j=0;j<col;++j) if (a[i][j]) {p=j;break;}
		for(int j=0;j<i;++j) 
			if (a[j][p]){
				int t = a[j][p];
				for(int k=p;k<=col;++k) a[j][k]=add(a[j][k],-mul(a[i][k],t));
			}
		for (int j=p+1;j<pre;++j){
			Free[fnum++]=j;
			x[j]=1;	// 自由元, 可赋任意值
		}
		pre=p;
		x[p]=a[i][col];
		for (int j=p+1;j<col;++j) x[p]=add(x[p],-mul(a[i][j],x[j]));
	}
	for (int i=0;i<pre;++i) Free[fnum++]=i;
}
int Gauss(int row, int col){
	r=0;
	for(int c=0;r<row&&c<col;++r,++c){
		int p=r;
		for (int i=r;i<row;++i) if (a[i][c]) {p=i;break;}
		if (p!=r) for (int i=c;i<=col;++i) swap(a[p][i],a[r][i]);
		if(!a[r][c]) {r--;continue;}
		int inv=kpow(a[r][c],mod-2);
		for (int i=c;i<=col;++i) a[r][i]=mul(a[r][i],inv);
		for (int i=r+1;i<row;++i) 
			if (a[i][c]){
				int t = a[i][c];
				for (int j=c;j<=col;++j) 
					a[i][j]=add(a[i][j],-mul(a[r][j], t));
			}
	}
	for (int i=r;i<row;++i) if (a[i][col]) return -1;//无解
	if(r<col){
		genx(col);
		return col - r;//自由变元个数
	}
	for (int i=col-1;i>=0;--i){
		int t = a[i][col];
		for (int j=i+1;j<col;++j) if (a[i][j]) t=add(t,-mul(a[i][j],x[j]));
		x[i]=t;
	}
	return 0;
}