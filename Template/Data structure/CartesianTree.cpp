struct node{
    int ls,rs,fa,idx,val;
    node(){}
    node(int a,int b){
        idx=a,val=b,ls=rs=fa=0;
    }
}tr[maxn]; 
int build(int *a,int n){	
    tr[0]=node(0,INF);
    for (int i=1;i<=n;++i){
        tr[i]=node(i,a[i]);
        int pos=i-1;
        /*
			若已知第i个数的最值区间为 l[i] 和 r[i]
			判断条件可改为 r[i] - l[i] > r[tr[pos].idx] - l[tr[pos].idx]
		*/
        while (tr[i].val>tr[pos].val)    //维护大根堆性质 
			pos=tr[pos].fa;	
        tr[i].ls=tr[pos].rs;
        tr[pos].rs=i;
        tr[i].fa=pos;
        tr[tr[i].ls].fa=i;
    }
    return tr[0].rs;
}
