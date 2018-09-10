void next(int* a,int n)
{
	for (int i=n-2;i>=0;--i)
	{
		if (a[i]<a[i+1])
		{
			int p=i+1;
			for (int j=p;j<n;++j)
			{
				if (a[j]>a[i])
					p=a[j]<a[p]?j:p;
			}
			swap(a[i],a[p]);
			reverse(a+i+1,a+n);
			return;
		}
	}
	reverse(a,a+n);
	return;
}
