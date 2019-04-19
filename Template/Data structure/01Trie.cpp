struct Trie_01
{
    static const int maxn=1e5+10,N = 32*maxn,M = 2;
    int node[N][M],value[N],rt,L; //value  记录对应节点的值，用于返回
    void init()
    { 
        fill_n(node[N-1],M,0);
        fill_n(value,N,0);
        L = 0;
        rt = newnode();
    }
    int newnode()
    {
        fill_n(node[L],M,0);
        return L++; 
    }
    void add(int x)
    {
        int p = rt;
        for (int i=31;i>=0;--i)
        {
            int idx = (x>>i)&1;
            if (!node[p][idx])
            {
                node[p][idx] = newnode();
            }
            p = node[p][idx];
            value[p]=min(value[p],x);
        }
    }
    int query(int x)
    {
        int p = rt;
        for (int i=31;i>=0;--i)
        {
            int idx = (x>>i)&1;
            if (node[p][idx^1])
                p = node[p][idx^1];
            else
                p = node[p][idx];
        }
        return value[p];
    }
};
