int fa[maxn],r[maxn];
void init(int n)
{
	for (int i=0;i<=n;++i)
		fa[i]=i;
}
int find(int x)
{
	if (fa[x]==x)
		return x;
	int tmp=fa[x];
	fa[x]=find(tmp);
	r[x]=(r[x]+r[tmp])%3;
	return fa[x];
}
int unio(int x,int y,int d)
{
	int fx=find(x),fy=find(y);
	if (fx!=fy)
	{
		r[fy]=(d+r[x]-r[y]+3)%3;
		fa[fy]=fx;
		return 0;
	}
	else  //if fx==fy,check
		return !((r[y]-r[x]+3)%3==d);
}
