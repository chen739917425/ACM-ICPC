/*
Nim:
	if xor_sum==0 
		first lose
	else 
		take xor_sum^a[i] (i:1->m)
Bash:
	if n%(m+1)==0
		first lose
Wythoff:
	if (x>y)
		swap(x,y);
	if x==int((sqrt(5)+1)/2)*(y-x)
		first lose
Fibonacci:
	if n in Fibonacci sequence
		first lose
*/
int S[1000],sg[10010];
bool visit[1005];
void SG(int n)
{
	int i,j;
	sg[0]=0;
	for (i=1;i<10005;++i)
	{
		memset(visit,0,sizeof(visit));
		for (j=0;j<n;++j)
			if (i-S[j]>=0)
				visit[sg[i-S[j]]]=1;
		for (j=0;j<=i;++j)
			if (visit[j]==0)
			{
				sg[i]=j;
				break;
			}
	}
}
