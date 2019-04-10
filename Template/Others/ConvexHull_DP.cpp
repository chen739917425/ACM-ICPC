// 当直线斜率不是单调变化时，队头元素不能出队，需要二分队列找最优决策点。
// 模板以维护下凸壳求最小值为例， 求最大值则相反

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
for (int i=1;i<=m;++i)
	f[1][i]=getf(0,i,1);
for (int k=2;k<=m;++k)
{
	h=t=0;
	q[0]=k-1;
	for (int j=k;j<=m;++j)
	{
		while (h<t&&dy(q[h+1],q[h],k-1)<=K*dx(q[h+1],q[h]))
			++h;
		f[k][j]=getf(q[h],j,k);
		while (h<t&&dy(j,q[t-1],k-1)*dx(q[t],q[t-1])<=dy(q[t],q[t-1],k-1)*dx(j,q[t-1]))
			--t;
		q[++t]=j;
	}
} 
