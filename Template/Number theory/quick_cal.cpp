ll kmul(ll a,ll b,ll mod)
{
    ll res=0;
    while (b)
    {
        if (b&1)
            res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}
ll kpow(ll a,ll b,ll mod)
{
    ll res=1;
    while (b)
    {
        if (b&1)
            res=kmul(res,a,mod)%mod;
        a=kmul(a,a,mod)%mod;
        b>>=1;
    }
    return res;
}

inline ll kmul(ll x,ll y,ll mod)//quick_multi O(1)
{
    ll tmp=(x*y-(ll)((ld)x/mod*y+1.0e-8)*mod);
    return tmp<0 ? tmp+mod : tmp;
}
