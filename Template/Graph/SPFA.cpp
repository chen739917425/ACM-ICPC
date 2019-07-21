/* 
	x-y<=z: y->x, weight=z
	x-y>=z: x->y, weight=-z
*/
int inq[maxn],vis[maxn],dis[maxn];
bool spfa(int s,int n){
	memset(dis,INF,sizeof(dis));
	dis[s]=0;	
	queue<int> q;
	q.push(s);
	inq[s]=1;
	while (sz(q)){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for (auto i:e[u]){
			int v=i.fi,w=i.se;
			if (dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				if (!inq[v]){
					if (++vis[v]>n)
						return 0;					
					inq[v]=1;
					q.push(v);

				}
			}
		}
	}
	return 1;
}
