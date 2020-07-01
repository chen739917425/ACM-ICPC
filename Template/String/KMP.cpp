int ne[maxn];
void init(char s[maxn],int n){	//index from 1 
	ne[1]=0;
	for (int i=2,j=0;i<=n;++i){
		while (s[j+1]!=s[i]&&j)	j=ne[j];
		j+=s[j+1]==s[i];
		ne[i]=j;
	}	
}
void match(char s[maxn],int n,char t[maxn],int m){	//get all positon of s appear in t
	int i=1,j=1;
	while (j<=m){
		if (s[i]==t[j]){
			++i,++j;
			if (i>n){
				/*	
					matched 
					start position = j - n
					do...
				*/
				i=ne[i-1]+1;
			}
		}
		else{
			if (i==1)	++j;
			else	i=ne[i-1]+1;
		}
	}
}
