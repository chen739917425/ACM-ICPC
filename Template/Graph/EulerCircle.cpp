/*
	欧拉回路存在判定： 
	无向图每个点的度数均为偶数
	有向图每个点的出度与入度相等
*/ 
struct E {
	int v,ne;
}e[N<<1]; 
int head[N],path[M],top,cnt=1;
bool vis[M];
void add(int u,int v) {
	e[++cnt].ne=head[u];
	e[cnt].v=v;
	head[u]=cnt;
} 
void dfs(int u) {
	for (int &i=head[u];i;i=e[i].ne) {
		if (vis[i]) continue;
		vis[i]=1;
		//vis[i^1]=1; 无向图的反向边
		dfs(e[i].v);
		path[++top]=v;
	}
}
