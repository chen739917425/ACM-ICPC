int id,rt[maxn],ne[maxn*24][2],cnt[maxn*24];
//ins(rt[i-1],rt[i]=++id,x)
void ins(int pre,int now,int x){
    for (int i=30;i>=0;--i){
        ne[now][0]=ne[pre][0];
        ne[now][1]=ne[pre][1];
        cnt[now]=cnt[pre]+1;
        int b=(x>>i)&1;
        ne[now][b]=++id;
        now=ne[now][b];
        pre=ne[pre][b];
    }
    cnt[now]=cnt[pre]+1;
}
int qry(int pre,int now,int x){ // 查询数组[pre+1,now]区间里的某个数与x异或的最大值
    int res=0;
    for (int i=30;i>=0;--i){
        int b=(x>>i)&1;
        if (cnt[ne[now][b^1]]>cnt[ne[pre][b^1]]){
            res^=(1<<i);
            now=ne[now][b^1];
            pre=ne[pre][b^1];
        }
        else{
            now=ne[now][b];
            pre=ne[pre][b];
        }
    }
    return res;
}
