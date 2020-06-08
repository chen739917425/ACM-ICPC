/*
	i : xi = 0
	i+n : xi = 1
	xi=p => xj=q : i+p*n -> j+q*n 
	xi or xj	 : i -> j+n, j -> i+n
	xi=p		 : i+(1-p)*n -> i+p*n
*/
bool two_SAT(){
	for (int i=1;i<=2*n;++i)
		if (!dfn[i])
			tarjan(i);
	for (int i=1;i<=n;++i){
		if (col[i]==col[i+n])
			return 0;
		value[i]=col[i]>col[i+n];
	}
	return 1;
}

