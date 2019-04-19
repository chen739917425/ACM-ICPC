struct Fenwick
{
    int fw[maxn];
    void add(int p,int c)
    {
        for (int i=p;i<maxn;i+=i&-i)
        	fw[i]+=c;
    }
    int qry(int p)
    {
        int res=0;
        for (int i=p;i;i-=i&-i)
        	res+=fw[i];
        return res;
    }
    int fw2[maxn][maxn];
    void add(int x,int y,int c)
    {
        for (int i=x;i<maxn;i+=i&-i)
        	for (int j=y;j<maxn;j+=j&-j)
        		fw[i][j]+=c;
    }
    int qry(int x,int y) //求前缀矩形和 
    {
        int res=0;
        for (int i=x;i;i-=i&-i)
        	for (int j=y;j;j-=j&-j)
        	res+=fw[i][j];
        return res;
    }
};
// 成段修改，单点求值(维护差分数组） 
// 1维
add(p,c),add(p+1,-c);
qry(p); //点p的值 
// 2维
add(x1,y1,c),add(x2+1,y2+1,c);
add(x1,y2+1,-c),add(x2+1,y1,-c);
qry(x,y); //(x,y)的值 
