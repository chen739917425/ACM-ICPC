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
/*  
	支持查询区间内的 异或最值 或 可构造性，动态插入数到末尾，贪心的思想维护前缀线性基
	可以离线 将查询的区间按r排序 内存不需要开N倍 只需要一倍
	bs[r][i].fi 表示前缀 r 第 i 位的基 
	bs[r][i].se 表示前缀 r 第 i 位的基由哪个位置的元素贡献
	贪心取靠后的元素来贡献
*/ 
P bs[maxn][32]; 
void insert(P p,int r){		// p = (a[r], r)
	for (int i=0;i<=30;++i)
		bs[r][i]=bs[r-1][i];
	for (int i=30;i>=0;--i){
		if ((p.fi>>i)&1){
			if (!bs[r][i].fi){
				bs[r][i]=p;
				return;
			} 
			if (bs[r][i].se<p.se)
				swap(bs[r][i],p);
			p.fi^=bs[r][i].fi;
		}
	}
}
ll getMax(int l,int r,ll res=0){	// res为初始值
	for (int i=30;i>=0;--i)
		if (bs[r][i].se>=l&&(res^bs[r][i].fi)>res)
			res^=bs[r][i].fi;
	return res;
}