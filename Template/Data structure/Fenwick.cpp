struct Fenwick
{
    int sum[maxn];
    void add(int p,int x)
    {
        while (p<=n)
        {
            sum[p]+=x;
            p+=p&-p;
        }
    }
    int qry(int p)
    {
        int res=0;
        while (p)
        {
            res+=sum[p];
            p-=p&-p;
        }
        return res;
    }
};
