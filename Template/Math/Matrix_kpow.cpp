struct matrix{
	static const int N=10;
	ll mat[N][N],n,m;
	matrix(){}
	matrix(ll a[N][N],int _n,int _m){
		n=_n,m=_m;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				mat[i][j]=a[i][j];
	}
	matrix(int _n,int _m,int v){
		n=_n,m=_m;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				mat[i][j]=i==j?v:0;
	}
	matrix operator + (const matrix& a) const{
		matrix res(n,a.m,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				res.mat[i][j]=add(mat[i][j],a.mat[i][j]);
		return res;
	}	
	matrix operator * (const matrix& a) const{
		matrix res(n,a.m,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<a.m;++j)
				for (int k=0;k<m;++k)
					res.mat[i][j]=add(res.mat[i][j],mul(mat[i][k],a.mat[k][j]));
		return res;
	}
	matrix operator ^ (ll b) const{
		matrix res(n,n,1),a=*this;
		while (b){
			if (b&1) res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	bool operator == (const matrix& a) const{
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				if (mat[i][j]!=a.mat[i][j])
					return 0;
		return 1;
	}	
};
