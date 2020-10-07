/* 	
当直线斜率不是单调变化时,队头元素不能出队,需要二分队列找最优决策点
当横坐标不单调变化时,CDQ分治
模板以维护下凸壳求最小值为例,求最大值则相反
*/
// 无分组与长度限制
h=t=0;
for (int j=1;j<=n;++j)
{
    while (h<t&&dy(q[h+1],q[h])<=K*dx(q[h+1],q[h]))
        ++h;
    f[j]=getf(q[h],j);
    while (h<t&&dy(j,q[t-1])*dx(q[t],q[t-1])<=dy(q[t],q[t-1])*dx(j,q[t-1]))
        --t;
    q[++t]=j;
}
// 有 k 长度限制
h=t=0;
for (int i=k;i<=n;++i)
{
    int j=i-k;
    if (j>=k)
    {
        while (h<t&&dy(j,q[t-1])*dx(q[t],q[t-1])<=dy(q[t],q[t-1])*dx(j,q[t-1]))
            --t;
        q[++t]=j;
    }
    while (h<t&&dy(q[h+1],q[h])<=K*dx(q[h+1],q[h]))
        ++h;
    f[i]=getf(q[h],i);
} 
// 有 m 分组数限制
for (int i=1;i<=n;++i)
	f[1][i]=getf(0,i,1);
for (int k=2;k<=m;++k)
{
	h=t=0;
	q[0]=k-1;
	for (int j=k;j<=n;++j)
	{
		while (h<t&&dy(q[h+1],q[h],k-1)<=K*dx(q[h+1],q[h]))
			++h;
		f[k][j]=getf(q[h],j,k);
		while (h<t&&dy(j,q[t-1],k-1)*dx(q[t],q[t-1])<=dy(q[t],q[t-1],k-1)*dx(j,q[t-1]))
			--t;
		q[++t]=j;
	}
} 
// 横坐标不单调
struct node{
	int id,k;
	bool operator<(node t) const{
		return k!=t.k?k<t.k:id<t.id;
	}
}
void cdq(int l,int r){ // sort by k before cdq(1,n)
	if (l==r){
		f[p[l].id]=max(f[p[l].id],f[p[l].id-1]);
		return;
	}
	// sort by id
	int m=(l+r)>>1,h=l,t=m+1,i;
	for (i=l;i<=r;++i)
		p[i].id<=m?tp[h++]=p[i]:tp[t++]=p[i];
	for (i=l;i<=r;++i)
		p[i]=tp[i];
	// ConvexHull DP
	cdq(l,m);
	h=0,t=-1;
	for (i=l;i<=m;++i){
		while (h<t&&dy(p[i].id,q[t-1])*dx(q[t],q[t-1])<=dy(q[t],q[t-1])*dx(p[i].id,q[t-1])) --t;
		q[++t]=p[i].id;
	}
	for (i=m+1;i<=r;++i){
		while (h<t&&dy(q[h+1],q[h])<=K(p[i].id)*dx(q[h+1],q[h])) ++h;
		f[p[i].id]=max(f[p[i].id],getf(p[i].id,q[h]));
	}
	cdq(m+1,r);
	// sort by X
	h=l,t=m+1,i=l;
	while (h<=m&&t<=r)
		tp[i++]=X(p[h].id)<X(p[t].id)? p[h++] : p[t++];
	while (h<=m) tp[i++]=p[h++];
	while (t<=r) tp[i++]=p[t++];
	for (i=l;i<=r;++i) p[i]=tp[i];
}