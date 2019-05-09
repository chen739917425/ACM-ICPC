#include<complex>
typedef complex<double> cp;
const double pi=acos(-1);
const int maxn=1e6;
int rev[maxn];
cp w[2][maxn];
void init(int n)
{
	int b=0;
	while ((1<<b)<n) ++b;
	for (int i=0;i<n;++i)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(b-1));
		w[0][i]=w[1][i]=cp(cos(2*pi*i/n),sin(2*pi*i/n)),w[1][i].imag(-w[0][i].imag());
	}
}
void fft(cp*a,int n,int f=0)	// f=0 => DFT, f=1 => IDFT
{
	cp c;
	for (int i=0; i<n; i++)
		if (i<rev[i]) 
			swap(a[i],a[rev[i]]);
	for (int l=2;l<=n;l<<=1)
		for (int i=0,t=n/l;i<n;i+=l)
			for (int j=0,k=0,m=l>>1;j<m;++j,k+=t) 
				c=w[f][k]*a[i+j+m],a[i+j+m]=a[i+j]-c,a[i+j]+=c;
	if (f) for (int i=0;i<n;++i) a[i]/=n;
}
cp a[maxn],b[maxn];
void work()
{
	read(a),read(b);
	int n=1;
	while (n<alen+blen)	n<<=1;
	init(n);
	fft(a,n);
	fft(b,n);
	for (int i=0;i<n;++i)
		a[i]*=b[i];
	fft(a,n,1);
}
