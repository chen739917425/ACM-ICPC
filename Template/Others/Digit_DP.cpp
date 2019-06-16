int dig[maxn];
ll pw[maxn];
P dp[maxn][5];
bool vis[maxn][5]; 
P dfs(int pos,int sta,int f){
	if (pos<0){
		return sta==3?mp(1,0):mp(0,0);
	}
	if (!f&&vis[pos][sta])
		return dp[pos][sta];
	int up=f?dig[pos]:9;
	P ans,tmp;
	ans.fi=0,ans.se=0;
	for (int i=0;i<=up;++i){
		if (sta==0){
			if (i==8)
				tmp=dfs(pos-1,1,f&&i==up);
			else
				tmp=dfs(pos-1,0,f&&i==up);
		}
		else if (sta==1){
			if (i==8)
				tmp=dfs(pos-1,2,f&&i==up);
			else 
				tmp=dfs(pos-1,0,f&&i==up);
		}
		else if (sta==2){
			if (i==6)
				tmp=dfs(pos-1,3,f&&i==up);
			else if (i==8)
				tmp=dfs(pos-1,2,f&&i==up);
			else
				tmp=dfs(pos-1,0,f&&i==up);
		}
		else
			tmp=dfs(pos-1,3,f&&i==up);
		ans.fi=add(ans.fi,tmp.fi);
		ans.se=add(ans.se,add(mul(mul(tmp.fi,i),pw[pos]),tmp.se));
	}
	if (!f)
		dp[pos][sta]=ans,vis[pos][sta]=1;
	return ans;
}
ll count(ll n){
	int pos=0;
	while (n){
		dig[pos++]=n%10;
		n/=10;
	}
	return dfs(pos-1,0,1).se;
}
