ll bs[70];
void insert(ll x)
{
    for (int i=62;i>=0;--i)
    {
        if (x&(1ll<<i))
        {
            if (!bs[i])
            {
                bs[i]=x;
                return;
            }
            x^=bs[i];
        }
    }
}
ll max_qry(ll init=0) // init为初始值，若没有，则置为0；
{
    for (int i=62;i>=0;--i)
        if ((init^bs[i])>init)
            init^=bs[i];
    return init;
}
ll min_qry(ll init=0)
{
	if (init==0)
	{
		for (int i=0;i<=62;++i)
			if (bs[i])
				return bs[i];
	}
	else
	{
   		for (int i=62;i>=0;--i)
        	if ((init^bs[i])<init)
            	init^=bs[i];
    	return init;
	}
}
bool check(ll x) //若基底的个数少于给定数的个数，则0可以被异或出来，需特判 
{
    for (int i=62;i>=0;--i)
        if (x&(1ll<<i))
            x^=bs[i];
    return x==0;
}
vector<ll> tmp;
ll kth_query(int k) //若0可以被异或出来，令k-- 
{
    for(int i=0;i<=62;++i)
    {
        if (!bs[i])
            continue;
        for(int j=i-1;j>=0;--j)
            if(bs[i]&(1ll<<j))
                bs[i]^=bs[j];
        tmp.pb(bs[i]);
    }
    if (k>=(1<<sz(tmp)))
        return -1;
    ll res=0;
    for(int i=0;i<sz(tmp);++i)
        if(k&(1ll<<i))
            res^=tmp[i];
    return res;
}
