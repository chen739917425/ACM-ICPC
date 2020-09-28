int dig[maxn];
ll pw[maxn]; // pw[i]=10^i
//贡献在回溯时计算的做法
struct data{
	int f,g,h;
	data(){}
	data(int a,int b,int c):f(a),g(b),h(c){}
}f[40][2][7][7];
int dig[maxn],pw[maxn];
data dfs(int pos,int ext,int sr,int vr,int lit){
    if (pos<0)    return data(!ext&&sr&&vr,0,0);
    if (!lit&&f[pos][ext][sr][vr].f!=-1)    return f[pos][ext][sr][vr];
    int up=lit?dig[pos]:9;
    data res=data(0,0,0);
    for (int i=0;i<=up;++i){
    	data tmp=dfs(pos-1,ext|(i==7),(sr+i)%7,(vr*10+i)%7,lit&&i==up);
    	res.f=add(res.f,tmp.f);
    	int t=mul(i,pw[pos]);
    	res.g=add(res.g,add(mul(t,tmp.f),tmp.g));
    	res.h=add(add(res.h,tmp.h),
      		mul(t,add(mul(t,tmp.f),mul(2,tmp.g))));
    }
    if (!lit)  f[pos][ext][sr][vr]=res;
    return res;
}

int count(ll n){
  	int pos=0;
    while (n){
        dig[pos++]=n%10;
        n/=10;
    }
    return dfs(pos-1,0,0,0,1).h;
}
//有前导零处理的做法
ll dfs(int pos,int sta,int k,int zr,int lit){
    if (pos<0)    return __builtin_popcount(sta)==k;
    if (!lit&&!zr&&f[pos][sta][k]!=-1)    return f[pos][sta][k];
    int up=lit?dig[pos]:9;
    ll res=0;
    for (int i=0;i<=up;++i){
    	if (zr&&!i)
    		res+=dfs(pos-1,sta,k,1,lit&&i==up);
    	else
			res+=dfs(pos-1,nextSta(sta,i),k,0,lit&&i==up);
    }
    if (!lit&&!zr)    f[pos][sta][k]=res;
    return res;
}
ll count(ll n){
	int pos=0;
    while (n){
        dig[pos++]=n%10;
        n/=10;
    }		
    return dfs(pos-1,0,k,1,1);
}

