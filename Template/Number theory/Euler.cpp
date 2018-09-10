/*
	A^B%C=A^(B%phi(C)+phi(C))%C
	x^phi(p)กิ1(mod p) -> inv[x]=x^(phi(p)-1)
*/
ll phi(ll n)//get phi(n)
{
    ll res=n;
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

ll phi[maxn],prime[maxn],pre[maxn];//make Euler_table
bool sign[maxn];
void phi_init()
{
	int cnt=0;
	phi[1]=1;
	for (int i=2;i<maxn;++i)
	{
		if (!sign[i])
		{
			prime[cnt++]=i;
			phi[i]=i-1;
		}
		for (int j=0;j<cnt&&i*prime[j]<maxn;++j)
		{
			sign[i*prime[j]]=1;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
