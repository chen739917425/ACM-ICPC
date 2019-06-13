void fwt(int* a,int n,int f=1){		// f=1 => FWT, f=-1 => UFWT
	int x,y;
	for (int l=2;l<=n;l<<=1)
		for (int i=0;i<n;i+=l)
			for (int j=0,m=l>>1;j<m;++j){
				and:x=a[i+j],y=a[i+j+m];
					a[i+j]=x+y*f;
				or: x=a[i+j];y=a[i+j+m];
					a[i+j+m]=y+x*f;
				xor:x=a[i+j],y=a[i+j+m];
					a[i+j]=x+y;a[i+j+m]=x-y;
					if (f==-1)
						a[i+j]/=2,a[i+j+m]/=2;			
			}
}
void work(){
	fwt(a,n);
	fwt(b,n);
	for (int i=0;i<n;++i)
		a[i]*=b[i];
	fwt(a,n,-1);
}
