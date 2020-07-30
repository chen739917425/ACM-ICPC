struct Trie{
    static const int maxn=1e5+10, N=32*maxn, M=2;	//M为子节点个数,M=2时为01_Trie
    int node[N][M],sum[N],rt,L;	//sum记录个数 
    //vector<int> v[N];			//记录每个子树下包含的数,求xor_mst时使用
    void init(){ 
        fill_n(node[N-1],M,0);
        fill_n(sum,N,0);
        L = 0;
        rt = newnode();
    }
    int newnode(){
        fill_n(node[L],M,0);
        return L++; 
    }
    void upd(int x,int c){	// c=1插入,c=-1删除
        int p=rt;
        sum[p]+=c;
        //v[p].pb(x);
        for (int i=30;i>=0;--i){
            int b = (x>>i)&1;
            if (!node[p][b])
                node[p][b] = newnode();
            p=node[p][b];
            sum[p]+=c;
            //v[p].pb(x);
        }
    }
    int qry(int x,int d=30,int p=0){		//返回与x异或的最值
        int res=0;
        for (int i=d;i>=0;--i){
            int b = (x>>i)&1;
			//查询异或最小值
            if (node[p][b]&&sum[node[p][b]])	
				p = node[p][b];
            else{
            	res^=1<<i;
                p = node[p][b^1];
            }
			/*查询异或最大值
            if (node[p][b^1]&&sum[node[p][b^1]]){
				res^=1<<i;
				p = node[p][b^1];
			}
            else
                p = node[p][b];		
			*/
        }
        return res;
    }
	/*定义任意两点间边权为点权异或值,求最小生成树
    ll ans;
    void dfs(int p,int d){
    	int c0=node[p][0],c1=node[p][1];
    	if (c0&&sum[c0])	
			dfs(c0,d-1);
    	if (c1&&sum[c1])	
			dfs(c1,d-1);
    	if (c0&&sum[c0]&&c1&&sum[c1]){
			if (sz(v[c0])>sz(v[c1]))	swap(c0,c1);
			int mn=(1ll<<31)-1;
			for (auto i:v[c0])
				mn=min(mn,(1<<d)+qry(i,d-1,c1));
			ans+=mn;
		}
    }
    ll xor_mst(){
    	ans=0;
    	dfs(rt,30);
    	return ans;
	}
	*/
}tr;
