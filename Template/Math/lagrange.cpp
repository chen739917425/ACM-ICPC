/*
	l(x) = Π(x-xj) 
	wi = 1/Π(xi-xj) 
	   = 1/(i-1)!/(n-i)!	if xi is consecutive (1->n)
	L(x) = l(x)*Σyi*wi/(x-xi)
*/ 
int lagrange(P* p,int n,int x){ // O(n^2)
	int lx=1,Lx=0;
	for (int i=1;i<=n;++i)
		lx=mul(lx,add(x,-p[i].fi));
	for (int i=1;i<=n;++i){
		int t=kpow(add(x,-p[i].fi),mod-2),wi=1;
		for (int j=1;j<=n;++j){
			if (i==j) continue;
			wi=mul(wi,add(p[i].fi,-p[j].fi));
		}
		wi=kpow(wi,mod-2);
		Lx=add(Lx,mul(mul(p[i].se,wi),t));
	}
	return mul(Lx,lx);
}
int lagrange(int* y,int n,int x){ // O(n) if xi from 1 to n
	if (x<=n)
		return y[x];
	int lx=1,Lx=0;
	for (int i=1;i<=n;++i)
		lx=mul(lx,add(x,-i));
	for (int i=1;i<=n;++i){
		int t=kpow(add(x,-i),mod-2),wi=mul(jc[i-1],jc[n-i]); //jc[x]=inv(x!)
		Lx=add(Lx,((n-i)%2?-1:1)*mul(mul(y[i],wi),t));
	}
	return mul(Lx,lx);
}
