bool e[maxn][maxn];
int n,ans,cnt[maxn],vis[maxn],clique[maxn];
bool dfs(int u,int dep) 
{
    for(int v=u+1;v<=n;++v)
	{
        if(cnt[v]+dep<=ans) 
			return 0;
		int i=0;
        while (i<dep&&e[v][vis[i]])
        	++i;
        if(i==dep)
		{  
            vis[dep]=v;
            if(dfs(v,dep+1))
				return 1;
        }    
    }    
    if(dep>ans)
	{
        ans=dep;
        for (int i=0;i<ans;++i)
        	clique[i]=vis[i];
        return 1;    
    }    
    return 0;
} 
void MaxClique()
{
    ans=-1;
    for(int i=n;i;i--)
    {
        vis[0]=i;
        dfs(i,1);
        cnt[i]=ans;
    }
}
