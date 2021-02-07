int d1[N],d2[N];
void upd(int l,int r,int h,int d){	// h 为首项, d 为公差 
	if (l>r)	return;
	d2[l]+=d;
	d2[r+1]-=d;
	d1[l]+=h-d;
	d1[r+1]-=h-d+(r-l+1)*d;
}
void work(int n){
	for (int i=1;i<=n;++i){
		d2[i]+=d2[i-1];
		d1[i]+=d2[i]+d1[i-1];
	}
}
