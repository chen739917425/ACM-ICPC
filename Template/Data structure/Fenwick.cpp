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
    int qry(int x,int y) //��ǰ׺���κ� 
    {
        int res=0;
        for (int i=x;i;i-=i&-i)
        	for (int j=y;j;j-=j&-j)
        	res+=fw[i][j];
        return res;
    }
};
// �ɶ��޸ģ�������ֵ(ά��������飩 
// 1ά
add(p,c),add(p+1,-c);
qry(p); //��p��ֵ 
// 2ά
add(x1,y1,c),add(x2+1,y2+1,c);
add(x1,y2+1,-c),add(x2+1,y1,-c);
qry(x,y); //(x,y)��ֵ 
