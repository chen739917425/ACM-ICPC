/*
	A^B%C =	A^(B%phi(C)), if (gcd(A,C)=1)
			A^(B%phi(C)+phi(C))%C, if (B>=phi(C))
	x^phi(p)กิ1(mod p) -> inv[x]=x^(phi(p)-1)
*/
int phi(int n)//get phi(n)
{
    int res=n;
    for (int i=2;i*i<=n;++i)
    {
        if (n%i==0)
            res=res/i*(i-1);
        while (n%i==0)
            n/=i;
    }
    if (n>1)
        res=res/n*(n-1);
    return res;
}

vector<int> prime;
bool vis[maxn];
int phi[maxn];
void phi_init() //make Euler_table
{
	phi[1]=1;
	for (int i=2;i<maxn;++i)
	{
		if (!vis[i])
		{
			prime.pb(i);
			phi[i]=i-1;
		}
		for (int j=0;j<sz(prime)&&ll(i)*prime[j]<maxn;++j)
		{
			int t=i*prime[j];
			vis[t]=1;
			if (i%prime[j])
				phi[t]=phi[i]*(prime[j]-1);
			else
			{
				phi[t]=prime[j]*phi[i];
				break;
			}
		}
	}
}

int mu[maxn];
void mu_init() //make Mobius_table
{
	mu[1]=1;
	for (int i=2;i<maxn;++i)
	{
		if (!vis[i])
			prime.pb(i),mu[i]=-1;
		for (int j=0;j<sz(prime)&&ll(i)*prime[j]<maxn;++j)
		{
			int t=i*prime[j];
			vis[t]=1;
			if (i%prime[j])
				mu[t]=-mu[i];
			else
			{
				mu[t]=0;
				break;
			}
		}
	}
}
