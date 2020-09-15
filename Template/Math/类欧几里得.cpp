inline int mul(ll a,ll b){
	a%=mod;
	b%=mod;
	return	a*b%mod;
}
inline int add(ll a,ll b){
	a+=b;
	a%=mod;
	if (a<0)	a+=mod;
	return a;
}
/*
	f(n,a,b,c) = Σ (a*i+b)/c 	(i∈[0,n])
	g(n,a,b,c) = Σ ((a*i+b)/c)*i (i∈[0,n])
	h(n,a,b,c) = Σ ((a*i+b)/c)^2 (i∈[0,n])
	a,b为负数时不能直接使用,应结合图形将a,b调整为等效的非负数
*/
struct F{
	ll f,g,h;
	F(){f=g=h=0;}
};
const int i2=inv(2),i6=inv(6);
F cal(ll n, ll a, ll b, ll c) {
	ll ac=a/c, bc=b/c, n1=n+1, n21=n*2+1;
	F r;
	if (!a){
		r.f = mul(bc,n1);
		r.g = mul(mul(mul(bc,n),n1),i2);
		r.h = (mul(mul(bc,bc),n1));
		return r;
	}
	if (a >= c || b >= c){
		r.f=add(
				mul(mul(mul(n,n1),i2),ac), 
				mul(bc,n1)
			);
		r.g=add(
				mul(mul(mul(mul(ac,n),n1),n21),i6),
				mul(mul(mul(bc,n),n1),i2)
			);
		r.h=add(
				add(
					mul(mul(mul(mul(mul(ac,ac),n),n1),n21),i6),
					mul(mul(bc,bc),n1)
				),
				mul(mul(mul(ac,bc),n),n1)
			);
		F t = cal(n,a%c,b%c,c);
		r.h=add(
				add(add(r.h,t.h), mul(mul(2,bc),t.f)),
				mul(mul(2,ac),t.g)
			);
		r.g = add(r.g, t.g);
		r.f = add(r.f, t.f);
		return r;
	}
	ll m=((__int128)a*n+b)/c;
	F t = cal(m-1, c, c-b-1, a);
	r.f = add(mul(n,m),-t.f);
	r.g = mul(add(add( mul(mul(m,n),n1), -t.h), -t.f), i2);
	r.h = add(add(add( mul(mul(n,m),m+1), -mul(2,t.g)), -mul(2,t.f)), -r.f);
	return r;
}
