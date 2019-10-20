// 枚举s的子集
for (int i=s;i;i=(i-1)&s)
	//do...
// 枚举s的超集
for (int i=s;i;i=(i+1)|s)
	//do...
// 枚举0~2^m-1的子集
for (int i=1;i<(1<<m);i<<=1)
	for (int j=0;j<(1<<m);++j)
		if (j&i)
			f[j]+=f[j^i];
// 枚举0~2^m-1的超集
for (int i=1;i<(1<<m);i<<=1)
	for (int j=0;j<(1<<m);++j)
		if (!(j&i))
			f[j]+=f[j^i];
