bool Mil_Rb(ll n,ll a)
{
    ll d=n-1,s=0,i;
    while (!(d&1))
    {
        d>>=1;
        s++;
    }
    ll t=kpow(a,d,n);
    if (t==1||t==-1)
        return 1;
    for (i=0;i<s;++i)
    {
        if (t==n-1)
            return 1;
        t=kmul(t,t,n);
    }
    return 0;
}
bool is_prime(ll n)
{
    ll i,a[4]={3,5,7,11};
    for (i=0;i<4;++i)
    {
        if (n==a[i])
            return 1;
        if (!n%a[i])
            return 0;
        if (n>a[i]&&!Mil_Rb(n,a[i]))
            return 0;
    }
    return 1;
}
