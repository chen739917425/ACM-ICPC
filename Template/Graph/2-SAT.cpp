/*
	i : xi = 0
	i+n : xi = 1
	i+p*n -> j+q*n : xi=p => xj=q (p,q∈{0,1}) 
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

